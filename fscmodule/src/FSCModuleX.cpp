/**
 * FSC X Module Abstraction
 *
 * Linker dependencies: version.lib dinput.lib dinput8.lib dxguid.lib
 */

#include "windows.h"

#include "SimConnect.h"

#include "FSCUtil.h"

/** callbacks */
void FSC_CALLBACK_ModuleLoaded(HANDLE hSim);
void FSC_CALLBACK_ModuleUnloaded(HANDLE hSim);
void FSC_CALLBACK_DispatchProc(HANDLE hSim, SIMCONNECT_RECV* pData);

/** module state */
struct {

	bool               quit;               // quit flags
	HINSTANCE          hInstance;          // instance handle
	char               cName[MAX_PATH];    // module name
	HANDLE             hSimConnect;        // sim connect handle
	HWND               hSimWindow;        // flight simulator window handle

} Module;

/** module name */
char* FSC_GetModuleName()
{
	return Module.cName;
}

/** module handle */
HINSTANCE FSC_GetModuleHandle()
{
	return Module.hInstance;
}

/** flight sim window */
HWND FSC_GetFlightSimWindow() {
	return Module.hSimWindow;
}

/** simulator dispatch */
void CALLBACK dispatch(SIMCONNECT_RECV* pData, DWORD cbData, void* ignore)
{
	// log dispatch success
    static bool callbackReceived = false;
	if (!callbackReceived) 
		FSC_Log("First SimConnect_CallDispatch callback");
	callbackReceived = true;

	if (pData->dwID==SIMCONNECT_RECV_ID_QUIT) {
		FSC_Log("SIMCONNECT_RECV_ID_QUIT");
        Module.quit = true;
		return;
	}

	if (pData->dwID==SIMCONNECT_RECV_ID_OPEN) {
		FSC_Log("SIMCONNECT_RECV_ID_OPEN");

		return;
	}

	FSC_CALLBACK_DispatchProc(Module.hSimConnect, pData);
}

/** init state */
void init(HINSTANCE hInstance) 
{

	// reset our globals
	memset(&Module, 0, sizeof(Module));

	// remember dll handle
	Module.hInstance = hInstance;

	// search for sim window
	Module.hSimWindow = FindWindow("FS98MAIN", NULL);
	if (Module.hSimWindow==NULL) {
		FSC_Log("FindWindow(\"FS98MAIN\") returned null");
		return;
	}

	// resolve name of module
	char path[MAX_PATH];
	GetModuleFileName(Module.hInstance, path, sizeof(path));
	char* pName = strrchr(path, '\\') + 1;
	*strrchr(path, '.') = '\0';
	strcpy_s(Module.cName, sizeof(Module.cName), pName);

	// done
}

/** sim connect */
bool connect()
{
	if (FAILED(SimConnect_Open(&Module.hSimConnect, FSC_GetModuleName(), NULL, 0, NULL, 0))) 
	{
		FSC_Log("Cannot establish connection to simulator");
		return false;
	}

	// done
	return true;
}

/** sim disconnect */
void disconnect()
{
	if (Module.hSimConnect!=NULL)
		SimConnect_Close(Module.hSimConnect);
}

/** first callback */
int __stdcall DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpvReserved)
{
	// first call?
	if (fdwReason!=DLL_PROCESS_ATTACH)
		return 0;

	// prep 
	init(hInstance);

	// don't need any more thread callbacks
	//DisableThreadLibraryCalls(hInstance);

	// log we're here
	FSC_Log("DLLMain");

	// done
	return true;
}

static VOID CALLBACK timer(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) 
{
	// log timer success
    static bool callbackReceived = false;
	if (!callbackReceived) 
		FSC_Log("First timer callback happened");
	callbackReceived = true;

	SimConnect_CallDispatch(Module.hSimConnect, dispatch, NULL);
}


/** start module  */
int __stdcall DLLStart(void)
{
	FSC_Log("DLLStart");

	// (sim)connect and trigger dispatch (DLL=one call is sufficient)
	if (connect()) 
	{
		// callback
		FSC_CALLBACK_ModuleLoaded(Module.hSimConnect);

		// trigger dispatch
		if (!SUCCEEDED(SimConnect_CallDispatch(Module.hSimConnect, dispatch, NULL)))
			FSC_Log("SimConnect_CallDispatch failed!");

		// setup a timer for cases where the auto dispatch doesn't work (timer=1)
		if (FSC_ReadBoolFromProfile("timer", false)) {
			FSC_Log("Enabling SimConnect_CallDispatch timer");
			SetTimer(FSC_GetFlightSimWindow(), WM_USER, 200, timer);
		}

	}

	// done
	return 0;
}

/** stop module */
void __stdcall DLLStop(void)
{
	FSC_Log("DLLStop");

	// callback
	FSC_CALLBACK_ModuleUnloaded(Module.hSimConnect);

	// dis(sim)connect 
	disconnect();
}

/** test main */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pargs, int nCmdShow)
{
	// prep
	init(hInstance);

	FSC_Log("WinMain");

	// connect and loop
	if (connect())
	{
		FSC_CALLBACK_ModuleLoaded(Module.hSimConnect);
		while (!Module.quit)
		{
			SimConnect_CallDispatch(Module.hSimConnect, dispatch, &Module);
			Sleep(1);
		} 
		FSC_CALLBACK_ModuleUnloaded(Module.hSimConnect);
		disconnect();
	}

	FSC_Log("/WinMain");

	// done
	return 0;
}


/**
 * add menu item
 */
bool FSC_AddMenu(unsigned int id, char path[], bool checked) {
	// TODO
	FSC_Log("Unsupported call to FSC_AddMenu");
	return false;
}

/**
 * change menu item
 */
bool FSC_ChangeMenu(unsigned int id, char path[], bool checked) {
	// TODO
	FSC_Log("Unsupported call to FSC_ChangeMenu");
	return false;
}

/**
 * Send a FS key event
 */
void FSC_TriggerKeyEvent(unsigned int key, unsigned int value) {
	// TODO
	FSC_Log("Unsupported call to FSC_TriggerKeyEvent");
}

/**
 * remove menu item
 */
bool FSC_RemoveMenu(unsigned int id) {
	// TODO
	FSC_Log("Unsupported call to FSC_RemoveMenu");
	return false;
}