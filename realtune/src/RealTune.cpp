#define _CRT_SECURE_NO_DEPRECATE 1

#ifndef _WIN32_WINNT        
#define _WIN32_WINNT 0x0501
#endif
#ifndef _WIN32_WINDOWS        
#define _WIN32_WINDOWS 0x0501
#endif
#include "FSCModule.h"
#include "stdio.h"

// our renderer for frequencies
typedef void (*RENDERER)(GAUGE_TOKEN token, char* text);

void RenderComNav(GAUGE_TOKEN token, char* text) {
	// 1xx.yy
	sprintf(text, "%.2f", 100 + FSC_GetNumberGaugeVar(token) / 100);
}
void RenderADF(GAUGE_TOKEN token, char* text) {
	// XYYY
	// x = ADF_EXTENDED_FREQUENCY&0xf00>8
	// y = ADF_FREQUENCY&0x0fff
	sprintf(text, "%04x", ((FSC_GetBCDGaugeVar(ADF_EXTENDED_FREQUENCY) & 0xf00) << 4) + FSC_GetBCDGaugeVar(ADF_FREQUENCY) );
}
void RenderTransponder(GAUGE_TOKEN token, char* text) {
	sprintf(text, "%04x", FSC_GetBCDGaugeVar(TRANSPONDER_CODE));
}


// a tunable radio
typedef struct {
	ID32 up, dn;
} DIGIT;

typedef struct {
	char name[16];
	GAUGE_TOKEN gauge1;
	GAUGE_TOKEN gauge2;
	RENDERER renderer;
	DIGIT digits[5];
	ID32 swap;
} RADIO;

#define ISBUTTON(btn) (uMsg==btn || (uMsg==WM_PARENTNOTIFY&&LOWORD(wParam)==btn))

// globals
RADIO radios[] = { 
	{ "Com 1"      , COM_STBY_FREQUENCY   , COM_FREQUENCY , &RenderComNav     , { {KEY_COM_RADIO_WHOLE_INC, KEY_COM_RADIO_WHOLE_DEC}, {KEY_COM_RADIO_FRACT_INC, KEY_COM_RADIO_FRACT_DEC}, {0,0} }, KEY_COM_RADIO_SWAP },
	{ "Com 2"      , COM2_STBY_FREQUENCY  , COM2_FREQUENCY, &RenderComNav     , { {KEY_COM2_RADIO_WHOLE_INC, KEY_COM2_RADIO_WHOLE_DEC}, {KEY_COM2_RADIO_FRACT_INC, KEY_COM2_RADIO_FRACT_DEC}, {0,0} }, KEY_COM2_RADIO_SWAP },
	{ "Nav 1"      , NAV1_STBY_FREQUENCY  , NAV1_FREQUENCY, &RenderComNav     , { {KEY_NAV1_RADIO_WHOLE_INC, KEY_NAV1_RADIO_WHOLE_DEC}, {KEY_NAV1_RADIO_FRACT_INC, KEY_NAV1_RADIO_FRACT_DEC}, {0,0} }, KEY_NAV1_RADIO_SWAP },
	{ "Nav 2"      , NAV2_STBY_FREQUENCY  , NAV2_FREQUENCY, &RenderComNav     , { {KEY_NAV2_RADIO_WHOLE_INC, KEY_NAV2_RADIO_WHOLE_DEC}, {KEY_NAV2_RADIO_FRACT_INC, KEY_NAV2_RADIO_FRACT_DEC}, {0,0} }, KEY_NAV2_RADIO_SWAP },
	{ "ADF 1"      , ADF_FREQUENCY   , MODULE_VAR_NONE    , &RenderADF        , { {KEY_ADF_100_INC, KEY_ADF_100_DEC}, {KEY_ADF_10_INC, KEY_ADF_10_DEC}, {KEY_ADF_1_INC, KEY_ADF_1_DEC}, {0,0} }, 0 },
	{ "Transponder", TRANSPONDER_CODE, MODULE_VAR_NONE    , &RenderTransponder, { {KEY_XPNDR_1000_INC, KEY_XPNDR_1000_DEC}, {KEY_XPNDR_100_INC, KEY_XPNDR_100_DEC}, {KEY_XPNDR_10_INC, KEY_XPNDR_10_DEC}, {KEY_XPNDR_1_INC, KEY_XPNDR_1_DEC}, {0,0} }, 0 },
};

bool isEnabled = true;
int cursor = -1;
int radio = 0;
char text[4096];
LONG lastWheel;

/**
 * show radios
 */
void ShowRadios() {
	strcpy(text, "RealTune\n");
	for (int i=0; i < sizeof(radios) / sizeof(RADIO); i++ ){
		strcat(text, i==radio&&cursor==0 ? " [" : "  ");
		strcat(text, radios[i].name);

		strcat(text, i==radio&&cursor>0 ? " [" : "  ");
		radios[i].renderer(radios[i].gauge1, text+strlen(text));
		strcat(text, i==radio&&cursor>0 ? "]" : "");

		if (radios[i].gauge2!=MODULE_VAR_NONE) {
			strcat(text, " > ");
			radios[i].renderer(radios[i].gauge2, text+strlen(text));
		}
		strcat(text, i==radio&&cursor==0 ? "]\n" : "\n");
	}

	FSC_DisplayAtis(text, FSC_ATIS_STATIC);
}
void HideRadios() {
	FSC_DisplayAtis(NULL, FSC_ATIS_STATIC);
}

/**
 * callback
 */
void FSC_CALLBACK_MenuChosen(unsigned int id) {
}

/**
 * callback
 */
void FSC_CALLBACK_ModuleLoaded(HWND hFlightSimWindow) {
	FSC_AddMenu(66666, "&Modules|Real&Tune|Enabled", isEnabled);
	FSC_AddMenu(66666, "&Modules|Real&Tune|Auto Ident", isEnabled);
}

/**
 * callback
 */
void FSC_CALLBACK_TimerElapsed() {

		// are we tuning?
		if (cursor>=0) {
			ShowRadios();
		}

}

/**
 * Handle aircraft change
 */ 
void FSC_CALLBACK_AircraftLoaded(PFSC_AIRCRAFT) {
}

/**
 * Handle windows event
 */
bool FSC_CALLBACK_WindowsEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// tuning right now?
	if (cursor>=0) {

		// cursor drill down?
		if (ISBUTTON(WM_LBUTTONDOWN)) {
			FSC_Log("Drill down into radio %d", radio);
			cursor++;
			if (radios[radio].digits[cursor-1].up==0) {
				// was last digit - swap?
				if (radios[radio].swap!=0) {
					FSC_Log("Swapping frequencies for radio %d", radio);
					FSC_TriggerKeyEvent(radios[radio].swap, 0);
				}
				// cursor reset
				cursor = -1;
				// and hide
				HideRadios();
				FSC_Log("Hiding radios");
			}
			// swallow
			return false;
		}

		// cursor popup?
		if (ISBUTTON(WM_MBUTTONDOWN)) {
			FSC_Log("Drill up from radio %d", radio);
			cursor--;
			if (cursor<0) {
				cursor = -1;
				HideRadios();
				FSC_Log("Hiding radios");
			}
			// swallow
			return false;
		} 

		// scroll in selection? (not twice for the same wheel message)
		if (uMsg==WM_MOUSEWHEEL && GetMessageTime()!=lastWheel) {

			lastWheel = GetMessageTime();

			int delta = GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? -1 : 1;

			FSC_Log("Wheel @ %d, delta %d", lastWheel, delta);

			if (cursor==0) {
				radio = (radio+delta)%(sizeof(radios) / sizeof(RADIO));
				FSC_Log("Switch to radio %d", radio);
			} else {
				ID32 key = delta>0 ? radios[radio].digits[cursor-1].dn : radios[radio].digits[cursor-1].up;
				FSC_Log("Tune radio %d, key %d", radio, key);
				FSC_TriggerKeyEvent( key , 0);
				return true;
			}
		}

	} else {

		// bring up tuner? 
		if (ISBUTTON(WM_MBUTTONDOWN)) {

			FSC_Log("Bring up radios");
			cursor = 0;

			// intercepted
			return false;
		}
	}

	// continue
	return true;
}

/**
 * Handle FS Key Event (KEY_ID_MIN++)
 * @return true if event can continue to FS, false otherwise
 */
bool FSC_CALLBACK_KeyEvent(ID32 key) {

	// ignored

	return true;
}

// test code for accessing transponder sby/transmit via FSUIP 
//// 0x7b91,1byte,0=XPDR Mode C,1=XPDRStandby
//HWND hFSUIPC = FindWindowEx(NULL, NULL, "UIPCMAIN", NULL);

//// 4 space for code pointer
//byte modeCharlie = 0;
//struct  {
//  DWORD result;
//  DWORD dwId;       
//  DWORD dwOffset;
//  DWORD nBytes;
//  void* pDest;
//  UINT32 eor;
//} request;
//request.dwId = 1;                    // FS6IPC_READSTATEDATA_ID
//request.dwOffset =  0x7b91;          // variable offset
//request.nBytes = 1;                  // number of bytes of state data to read
//request.pDest = (PVOID)&modeCharlie; // destination buffer for data (client use only)
//request.eor = 0;

//UINT msg = WM_USER+130; // WM_IPCTHREADACCESS;

//DWORD dwError = SendMessage(hFSUIPC, msg, sizeof(request), (LPARAM) &request);

//FSC_Log("FSUIPC %d,%d", hFSUIPC,dwError);