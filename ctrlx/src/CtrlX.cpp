#include "FSCUtil.h"
#include "FSCJoy.h"
#include "FSCModuleX.h"

#include "Ctrl.h"

/** consts */
static enum EVENT_ID{
	EVENT_TIMER
};

static enum DEFINITION_ID {
	SET_GEAR_POSITION
};

/** module state */
CTRL ctrl;
WNDPROC pSimWindowProc;
HANDLE hSim;


/** callback - dispatch*/
void FSC_CALLBACK_DispatchProc(HANDLE hSim, SIMCONNECT_RECV* pRecv)
{
	SIMCONNECT_RECV_(EVENT, pEvent, pRecv);
	if (pEvent) switch (pEvent->uEventID)
	{
		// timer for joystick background check?
		case EVENT_TIMER:
			ctrl_timer(&ctrl);
			break;
	}

}

/** window proc interceptor */
LRESULT CALLBACK InterceptingWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	//// key down kneeboard is interested in?
	//if (uMsg==WM_KEYDOWN) {
	//	boolean isCtrl = (GetKeyState(VK_CONTROL)&0x8000) != 0;
	//	if (isCtrl && wParam=='X' ) {
	//	}
	//}

	// continue with original
	return CallWindowProc(pSimWindowProc, hwnd, uMsg, wParam, lParam);
}

/** callback - module up */
void FSC_CALLBACK_ModuleLoaded(HANDLE setHSim) 
{

	FSC_Log("Loading Ivent");

	// init state
	hSim = setHSim;
	ctrl_init(&ctrl);

	// hook up to window events
	pSimWindowProc = (WNDPROC)SetWindowLong(FSC_GetFlightSimWindow(), GWL_WNDPROC, (LONG)InterceptingWindowProc);
	if (pSimWindowProc==0) {
		char message[] = "SetWindowLong(\"handle, GWL_WNDPROC, proc\") returned null - Ievent keyboard bindings won't work";
		FSC_Log(message);
		MessageBox(NULL, message, "Ievent", MB_OK | MB_ICONEXCLAMATION);
	}

	// prepare event handling
	SimConnect_SubscribeToSystemEvent(hSim, EVENT_TIMER, "6Hz");

	SimConnect_AddToDataDefinition(hSim, SET_GEAR_POSITION, "GEAR HANDLE POSITION", "Bool", SIMCONNECT_DATATYPE_INT32);
}

/** callback - module down */
void FSC_CALLBACK_ModuleUnloaded(HANDLE hSim)
{
	FSC_Log("Unloading Ivent");
}

void ctrl_set_gear(CTRL* ctrl, int gear) {

	SimConnect_SetDataOnSimObject(hSim, SET_GEAR_POSITION, SIMCONNECT_OBJECT_ID_USER, 0, 1, sizeof(gear), &gear);

}
