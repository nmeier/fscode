#include "FSCModuleX.h"
#include "FSCUtil.h"

#include "PDFView.h"
#include "PDFKneeboard.h"

/** consts */
static enum EVENT_ID{
	EVENT_MENU,
	EVENT_MENU_SHOW,
	EVENT_MENU_HIDE,
	EVENT_MENU_OPEN,
	EVENT_MENU_CLOSE,
	EVENT_MENU_SETTINGS,
    EVENT_SIM,
	EVENT_TIMER
};


WNDPROC pSimWindowProc;

/** window proc interceptor */
LRESULT CALLBACK InterceptingWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// key down kneeboard is interested in?
	if (uMsg==WM_KEYDOWN && kneeboard_keydown(wParam))
		return false;

	// key up kneeboard is interested in?
	if (uMsg==WM_KEYUP && kneeboard_keyup(wParam))
		return false;

	// a window close?
	if (uMsg==WM_CLOSE)
	{
		// close all saving state
		kneeboard_close();
	}

	// continue with original
	return CallWindowProc(pSimWindowProc, hwnd, uMsg, wParam, lParam);
}

/** callback for simconnect data */
void FSC_CALLBACK_DispatchProc(HANDLE hSim, SIMCONNECT_RECV* pRecv)
{
	SIMCONNECT_RECV_(EVENT, pEvent, pRecv);
	if (pEvent) switch (pEvent->uEventID)
	{
		// hide kneeboard on sim stop
		case EVENT_SIM:
			if (!pEvent->dwData)
				pdfview_hide();
			break;
		// timer for joystick background check?
		case EVENT_TIMER:
			kneeboard_timer();
			break;
		// menus
		case EVENT_MENU_SHOW:
			pdfview_show();
			break;
		case EVENT_MENU_HIDE:
			pdfview_hide();
			break;
		case EVENT_MENU_OPEN:
			open_document();
			break;
		case EVENT_MENU_CLOSE:
			close_document();
			break;
		case EVENT_MENU_SETTINGS:
			SimConnect_SetSystemState(hSim, "DialogMode", 1, 0, NULL);
			kneeboard_settings();
			SimConnect_SetSystemState(hSim, "DialogMode", 0, 0, NULL);
			break;
	}


}

/** callback for module loaded */
void FSC_CALLBACK_ModuleLoaded(HANDLE hSim) 
{
	FSC_Log("Initializing Kneeboard");
	kneeboard_init(FSC_GetFlightSimWindow(), FSC_GetModuleHandle());

	// hook up into window events
	pSimWindowProc = (WNDPROC)SetWindowLong(FSC_GetFlightSimWindow(), GWL_WNDPROC, (LONG)InterceptingWindowProc);
	if (pSimWindowProc==0) {
		char message[] = "SetWindowLong(\"handle, GWL_WNDPROC, proc\") returned null - PDFKneeboard keyboard shortcuts won't work";
		FSC_Log(message);
		MessageBox(NULL, message, "PDFKneeboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	// start listening
	SimConnect_SubscribeToSystemEvent(hSim, EVENT_TIMER, "6Hz");
	SimConnect_SubscribeToSystemEvent(hSim, EVENT_SIM, "Sim");

	// setup menus
	SimConnect_MenuAddItem(hSim, "&PDFKneeboard", EVENT_MENU, 0);
	SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "Show &Kneeboard", EVENT_MENU_SHOW, 0);
	SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "&Hide Kneeboard", EVENT_MENU_HIDE, 0);
	SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "&Open Document", EVENT_MENU_OPEN, 0);
	SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "&Close Document", EVENT_MENU_CLOSE, 0);
	SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "&Settings...", EVENT_MENU_SETTINGS, 0);


	// done
}

/** callback - module down */
void FSC_CALLBACK_ModuleUnloaded(HANDLE hSim)
{
	// unhook from window events
	SetWindowLong(FSC_GetFlightSimWindow(), GWL_WNDPROC, (LONG)pSimWindowProc);

	// done
	FSC_Log("Kneeboard unloaded");
}
