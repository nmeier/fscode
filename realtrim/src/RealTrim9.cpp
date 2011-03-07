
#include "FSCModule.h"
#include "FSCAir.h"
#include "FSCUtil.h"
#include "FSCJoy.h"

#include "RealTrim.h"

#include "stdio.h"

/** our defines */
#define	MENU_ID_SETUP	44444
#define MENU_ID_ADJUSTTRIMINC 44446
#define MENU_ID_TRIMWITHMWHEEL 44447
#define MENU_SETUP "&Modules|&RealTrim|Trim &Button..."
#define MENU_ADJUSTTRIMINC "&Modules|&RealTrim|&Adjust Trim Increments"
#define MENU_TRIMWITHMWHEEL "&Modules|&RealTrim|Trim with &Mouse Wheel"

#define DEFAULT_TRIM_FREQUENCY 20 // 20hz (20 times a second)

struct REALTRIM9 : public REALTRIM
{
	ID32 deferredKeyTrim;

	bool isAdjustTrimIncrements; // whether we're adjusting FS's up/down trimming
	bool isTrimWithMouseWheel; // whether we intercept mouse wheel for trimming
	LONG lastTrimWithMouseWheel;   // last time the mouse wheel was used

};

// global state
REALTRIM9 realtrim;

// callback
void FSC_CALLBACK_ModuleLoaded(HWND hFlightSimWindow, HMODULE hModule) {

	realtrim_init(&realtrim);

	realtrim.isAdjustTrimIncrements = true; // whether we're adjusting FS's up/down trimming
	realtrim.isTrimWithMouseWheel = false; // whether we intercept mouse wheel for trimming
	realtrim.lastTrimWithMouseWheel = 0;   // last time the mouse wheel was used
	realtrim.deferredKeyTrim = 0;

	realtrim.isAdjustTrimIncrements = FSC_ReadBoolFromProfile(INI_KEY_ADJUSTTRIMINC, realtrim.isAdjustTrimIncrements);
	realtrim.isTrimWithMouseWheel = FSC_ReadBoolFromProfile(INI_KEY_TRIMWITHMWHEEL, realtrim.isTrimWithMouseWheel);


	// add menus
	FSC_AddMenu(MENU_ID_SETUP, MENU_SETUP, false);
	FSC_AddMenu(MENU_ID_ADJUSTTRIMINC, MENU_ADJUSTTRIMINC, realtrim.isAdjustTrimIncrements);
	FSC_AddMenu(MENU_ID_TRIMWITHMWHEEL, MENU_TRIMWITHMWHEEL, realtrim.isTrimWithMouseWheel);

	// start timer
	int hertz = FSC_ReadIntFromProfile(INI_KEY_FREQUENCY, DEFAULT_TRIM_FREQUENCY);
	FSC_SetTimerCallback(hertz);

}
void FSC_CALLBACK_ModuleUnloaded() 
{
}

void realtrim_trim(REALTRIM* pRealtrim, double trimDeflection)
{
	// in FS9 we have to find the matching trim wheel position (-16383 to +16383) for given radian
	UINT32 trimWheelPosition = (UINT32)( trimDeflection / pRealtrim->elevatorTrimLimit * 16383 );
	FSC_TriggerKeyEvent(KEY_AXIS_ELEV_TRIM_SET, -trimWheelPosition);
}

void realtrim_report(REALTRIM* pRealtrim, char* message)
{
	FSC_DisplayAtis(message, FSC_ATIS_WHITE);
}

// callback
void FSC_CALLBACK_MenuChosen(unsigned int id) {

	if (id==MENU_ID_SETUP) {
		realtrim_getbutton(&realtrim);
		return;
	}
	if (id==MENU_ID_ADJUSTTRIMINC) {
		realtrim.isAdjustTrimIncrements = !realtrim.isAdjustTrimIncrements;
		FSC_WriteBoolToProfile(INI_KEY_ADJUSTTRIMINC, realtrim.isAdjustTrimIncrements);
		FSC_ChangeMenu(MENU_ID_ADJUSTTRIMINC, MENU_ADJUSTTRIMINC, realtrim.isAdjustTrimIncrements);

		return;
	}
	if (id==MENU_ID_TRIMWITHMWHEEL) {
		realtrim.isTrimWithMouseWheel = !realtrim.isTrimWithMouseWheel;
		FSC_WriteBoolToProfile(INI_KEY_TRIMWITHMWHEEL, realtrim.isTrimWithMouseWheel);
		FSC_ChangeMenu(MENU_ID_TRIMWITHMWHEEL, MENU_TRIMWITHMWHEEL, realtrim.isTrimWithMouseWheel);

		return;
	}
}

// trim callback
void FSC_CALLBACK_TimerElapsed() {

	// trim
	FLOAT64 elevatorDeflection = FSC_GetNumberGaugeVar(ELEVATOR_DEFLECTION);
	FLOAT64 trimDeflection = FSC_GetNumberGaugeVar(ELEVATOR_TRIM);
	realtrim_trim(&realtrim, elevatorDeflection, trimDeflection, FSC_IsAutopilotOn());

	// deferred trim key?
	if (realtrim.deferredKeyTrim!=0) {

		// trim by a 1/4 degree per click
		FLOAT64 trim = FSC_GetNumberGaugeVar(ELEVATOR_TRIM);
		FLOAT64 delta = (2*PI) / 360.0 / 4;
		if (realtrim.deferredKeyTrim==KEY_ELEV_TRIM_DN) 
			trim -= delta;
		else {
			trim += delta;
		}
		// set trim input
		UINT32 input = (UINT32)(int)(trim / realtrim.elevatorTrimLimit * 16383);
		FSC_TriggerKeyEvent(KEY_ELEVATOR_TRIM_SET, input);

		// done for now
		realtrim.deferredKeyTrim = 0;
	}

	// done		
}

// callback
void FSC_CALLBACK_AircraftLoaded(PFSC_AIRCRAFT pAircraft) {	

	realtrim_reload(&realtrim, pAircraft->airfile, pAircraft->cfgfile);

}

// callback
bool FSC_CALLBACK_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {

		// trim via mouse wheel?
		case WM_MOUSEWHEEL:

			// trimming with wheel?
			if (!realtrim.isTrimWithMouseWheel)
				break;

			// make sure it's really for us (don't want to steel wheel from pdfkneeboard for example)
			POINT p;
			p.x = LOWORD(lParam); 
			p.y = HIWORD(lParam); 
			HWND tst = WindowFromPoint(p);
			if (IsChild(hwnd, tst)==0)
				break;

			// modifier or autopilot?
			if (GET_KEYSTATE_WPARAM(wParam)!=0 || FSC_IsAutopilotOn()) 
				break;

			// this happens twice sometimes
			if (GetMessageTime()!=realtrim.lastTrimWithMouseWheel) {
				realtrim.lastTrimWithMouseWheel = GetMessageTime();

				// wheel standard unit is 120 = 1/4 degree 
				FLOAT64 trim = FSC_GetNumberGaugeVar(ELEVATOR_TRIM)
				 - (2*PI) / 360.0 / 4 / 120 * GET_WHEEL_DELTA_WPARAM(wParam);
				// set trim input
				int input = (int)(trim / realtrim.elevatorTrimLimit * 16383);
				FSC_TriggerKeyEvent(KEY_ELEVATOR_TRIM_SET, input);

				return false;
			}
			break;
	}

	// continue
	return true;
}

// callback
bool FSC_CALLBACK_KeyEvent(ID32 key) {

	// flight simulator trim key 
	if (key==KEY_ELEV_TRIM_DN || key==KEY_ELEV_TRIM_UP) {
		if (realtrim.isAdjustTrimIncrements && !FSC_IsAutopilotOn()) {
			realtrim.deferredKeyTrim = key;
			return false;
		}
	}

	// continue
	return true;
}