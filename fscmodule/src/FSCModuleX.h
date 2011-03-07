#include <windows.h>

#include "SimConnect.h"

#define SIMCONNECT_RECV_(type,dest,source) SIMCONNECT_RECV_##type* dest = (source->dwID!=SIMCONNECT_RECV_ID_##type ? NULL : (SIMCONNECT_RECV_##type*)source)

/** module handle */
HINSTANCE FSC_GetModuleHandle();

/** module name */
char* FSC_GetModuleName();

/** flight sim window */
HWND FSC_GetFlightSimWindow();

// Callbacks to be defined in module

/**
 * simulator event callback (simconnect abstraction layer)
 */
void FSC_CALLBACK_DispatchProc(HANDLE hSim, SIMCONNECT_RECV* pData);

/**
 * module initialization
 */
void FSC_CALLBACK_ModuleLoaded(HANDLE hSim);
void FSC_CALLBACK_ModuleUnloaded(HANDLE hSim);

