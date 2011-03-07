#define _CRT_SECURE_NO_DEPRECATE 1

#ifndef _WIN32_WINNT        
#define _WIN32_WINNT 0x0501
#endif
#ifndef _WIN32_WINDOWS        
#define _WIN32_WINDOWS 0x0501
#endif

#include "FSCModule.h"
#include "FSCUtil.h"
#include "stdio.h"

#define	MENU_ID_RELOAD 44777

#define MAX_BINDINGS 64

struct binding_s
{
	int id;
	char name[MAX_PATH];
	char exec[MAX_PATH];
};

struct launcher_s
{
	int numBindings;
	binding_s bindings[MAX_BINDINGS];
}
launcher;

void reload()
{
	// remove current menu entries
	for (int i=0;i<launcher.numBindings;i++)
		FSC_RemoveMenu(launcher.bindings[i].id);

	// start anew
	launcher.numBindings = 0;

	char tmp[MAX_PATH];
	while (true) {

		sprintf_s(tmp, sizeof(tmp), "name.%d", launcher.numBindings);
		FSC_ReadStringFromProfile(tmp, launcher.bindings[launcher.numBindings].name, sizeof(launcher.bindings[launcher.numBindings].name), "");
		sprintf_s(tmp, sizeof(tmp), "exec.%d", launcher.numBindings);
		FSC_ReadStringFromProfile(tmp, launcher.bindings[launcher.numBindings].exec, sizeof(launcher.bindings[launcher.numBindings].exec), "");

		if (strlen(launcher.bindings[launcher.numBindings].name)==0)
			break;

		FSC_Log("Found binding %s for executable %s", launcher.bindings[launcher.numBindings].name, launcher.bindings[launcher.numBindings].exec);

		sprintf_s(tmp, sizeof(tmp), "&Modules|&Launcher|&%s", launcher.bindings[launcher.numBindings].name);

		launcher.numBindings++;

		FSC_AddMenu(MENU_ID_RELOAD+launcher.numBindings, tmp, false);

	}

	FSC_Log("Found total of %d bindings", launcher.numBindings);

	FSC_AddMenu(MENU_ID_RELOAD, "&Modules|&Launcher|&Reload", false);

}

/**
 * module initialization
 */
void FSC_CALLBACK_ModuleLoaded(HWND hFlightSimWindow, HMODULE hModule)
{
	memset(&launcher, 0, sizeof(launcher));

	reload();
}

/**
 * menu callback
 */
void FSC_CALLBACK_MenuChosen(unsigned int id)
{
	if (id==MENU_ID_RELOAD) {
		reload();
		return;
	}

	int b = id-MENU_ID_RELOAD-1;
	if (b>=0 && b<launcher.numBindings) {
		FSC_Log("Launching %s", launcher.bindings[b].exec);
		STARTUPINFO si; memset(&si, 0, sizeof(si));
		PROCESS_INFORMATION pi; memset(&pi, 0, sizeof(pi));
		if (0==CreateProcess(NULL, launcher.bindings[b].exec, NULL, NULL, false, 0, NULL, NULL, &si, &pi)) {
			FSC_Log("Launch of %s failed, last error = %d", launcher.bindings[b].exec, GetLastError());
		}
	}

}

void FSC_CALLBACK_ModuleUnloaded()
{
}

/**
 * timed callback
 */
void FSC_CALLBACK_TimerElapsed()
{
}

/**
 * Handle aircraft change
 */ 
void FSC_CALLBACK_AircraftLoaded(PFSC_AIRCRAFT paircraft)
{
}

/**
 * Handle windows event
 */
bool FSC_CALLBACK_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	return true;
}

/**
 * Handle FS Key Event (KEY_ID_MIN++)
 * @return true if event can continue to FS, false otherwise
 */
bool FSC_CALLBACK_KeyEvent(ID32 key)
{
	return true;
}
