#include <stdio.h>

#include "FSCModule.h"
#include "FSCUtil.h"
#include "FSCJoy.h"

#include "PDFView.h"
#include "PDFKneeboard.h"

#define	MENU_ID_SHOW     44555
#define MENU_ID_HIDE     44556
#define MENU_ID_OPEN     44557
#define	MENU_ID_CLOSE    44558
#define MENU_ID_SETTINGS 44559

#define MENU_SHOW "&Modules|&PDFKneeboard|Show &Kneeboard"
#define MENU_HIDE "&Modules|&PDFKneeboard|&Hide Kneeboard"
#define MENU_OPEN "&Modules|&PDFKneeboard|&Open Document"
#define MENU_CLOSE "&Modules|&PDFKneeboard|&Close Document"
#define MENU_SETTINGS "&Modules|&PDFKneeboard|Settings..."


/**
 * module initialization
 */
void FSC_CALLBACK_ModuleLoaded(HWND hFlightSimWindow, HMODULE hModule)
{
	kneeboard_init(hFlightSimWindow, hModule);

	FSC_AddMenu(MENU_ID_SHOW, MENU_SHOW, false);
	FSC_AddMenu(MENU_ID_HIDE, MENU_HIDE, false);
	FSC_AddMenu(MENU_ID_OPEN, MENU_OPEN, false);
	FSC_AddMenu(MENU_ID_CLOSE, MENU_CLOSE, false);
	FSC_AddMenu(MENU_ID_SETTINGS, MENU_SETTINGS, false);

	FSC_SetTimerCallback(20);

}

void FSC_CALLBACK_ModuleUnloaded() {
}

/**
 * Handle aircraft change
 */ 
void FSC_CALLBACK_AircraftLoaded(PFSC_AIRCRAFT)
{
}


/**
 * menu callback
 */
void FSC_CALLBACK_MenuChosen(unsigned int id) 
{
	switch (id) {
		case MENU_ID_SHOW:
			pdfview_show();
			break;
		case MENU_ID_HIDE:
			pdfview_hide();
			break;
		case MENU_ID_OPEN:
			open_document();
			break;
		case MENU_ID_CLOSE:
			close_document();
			break;
		case MENU_ID_SETTINGS:
			kneeboard_settings();
			break;
	}
}

/**
 * timed callback
 */
void FSC_CALLBACK_TimerElapsed()
{
	kneeboard_timer();
}


/**
 * Handle windows event
 */
bool FSC_CALLBACK_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// key down kneeboard is interested in?
	if (uMsg==WM_KEYDOWN && kneeboard_keydown(wParam))
		return false;

	// key up kneeboard is interested in?
	if (uMsg==WM_KEYUP && kneeboard_keyup(wParam))
		return false;

	// closing window?
	if (uMsg==WM_CLOSE) 
	{
		FSC_Log("WM_CLOSE saving kneeboard state");
		kneeboard_close();
		pdfview_hide();
	}

	// continue
	return true;
}

/**
 * Handle FS Key Event (KEY_ID_MIN++)
 * @return true if event can continue to FS, false otherwise
 */
bool FSC_CALLBACK_KeyEvent(ID32 key)
{
	// continue
	return true;
}
