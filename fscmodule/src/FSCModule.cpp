/**
* FSCModule - a Flight Simulator FS2004 module skeleton
* Copyright (c) 2006-2008, Nils Meier
*/

/*********************************************************************************
**************************** includes/dependencies *******************************
*********************************************************************************/

#include <windows.h>
#include <winver.h>
#include <stdio.h>
#include <commctrl.h>
#include <string.h>
#include <time.h>

#include "FSCModule.h"
#include "FSCUtil.h"

/*********************************************************************************
*************************** constants & definitions ******************************
*********************************************************************************/

void FSAPI InitModule(void);
void FSAPI DeinitModule(void);

#define FS_DISPLAY_ATIS_MODE_STATIC 7
#define FS_DISPLAY_ATIS_MODE_SCROLL_YELLOW 1
#define FS_DISPLAY_ATIS_MODE_SCROLL_GREEN 2
#define FS_DISPLAY_ATIS_MODE_SCROLL_WHITE 3
#define FS_DISPLAY_ATIS_MODE_SCROLL_RED 6

typedef struct {
  long unknown1[50];
  void (FSAPI * DisplayAtis)(char* text,int mode,int time,int keep);
  long unknown2[21];
} FS_WINDOW_API, *PFS_WINDOW_API;

typedef struct FS_AIRCRAFT {
	char a[12];
	char folder[MAX_PATH];
	char b[4];
	char name[256];
	char description[1024];
	char performance[1024];
	char airfile[264];
	char manufacturer[260];
	char model[260];
	char color[264];
	char callsign[8];
	char c[104];
	char modelfile[520];
} FS_AIRCRAFT, *PFS_AIRCRAFT;

struct FS_LOADAIRCRAFT_EVENT {
	int a,b;
	PFS_AIRCRAFT pAircraft;
};

typedef struct _MODULE_LINKAGE {
	FSLINKAGE
	PVOID ModuleTable;
} MODULE_LINKAGE;

typedef struct _FS9
{
	FSLINKAGE
	BOOL		(FSAPI *ignored[266]) (void);
	GAUGE_KEY_EVENT_HANDLER pGaugeKeyEventHandler;
} FS9_API, *PFS9_API;

typedef struct _MODULE_IMPORT {
	ID idPanels;
	PPANELS pPanels;
	ID idFS9Api;
	PFS9_API pFS9Api;
	ID idWindowApi;
	PFS_WINDOW_API pWindowApi;
	ID idNULL;
	PVOID pNULL;
} MODULE_IMPORT;

#define INI_KEY_LOGGING "Logging"

/*********************************************************************************
******************************** global variables *******************************
*********************************************************************************/

typedef void (FSAPI *EVENTFUNC)(ID32 event_id, UINT32 code, PVOID user_data);

struct {

	HINSTANCE          hDLL;               // dll instance handle
	char               cName[MAX_PATH];    // module name
	FILE*              pLogFile;           // log filehandle
	UINT_PTR           iTimer;             // module timer

	GAUGE_KEY_EVENT_HANDLER pfsGaugeKeyEventHandler; // flight simulator internal gauge event handler
	WNDPROC            pSimWindowProc;    // flight simulator window procedure
	HWND               hSimWindow;        // flight simulator window handle

	HWND               hMessageWindow;   // current message window handle
	char*              pMessageAction;   // current message window action string

	FSC_AIRCRAFT       fscAircraft;      // flight simulator current aircraft

	struct {
		unsigned int id;
		char path[MAX_PATH];
		bool checked;
	} menus[FSC_MAX_MENUS];

} Module;


/** import table managed by FS9 */
extern "C" DLLEXPORT MODULE_IMPORT ImportTable = { 
	0x0000000F, (PPANELS)NULL,
	0x00000001, (PFS9_API)NULL,
	//0x00000019, (PSIM1)NULL, 
	0x0000000A, (PFS_WINDOW_API)NULL,
	0x00000000, NULL
};

/** export table considered by FS9 */
extern "C" DLLEXPORT MODULE_LINKAGE Linkage = { 
	0x00000000,
	InitModule,
	DeinitModule,
	0,
	0,
	0x0900, // 0x0900 FS2004 / 0x0800 FS2002 - we're setting this in DllMain
	NULL
};

/** module name resolver */
char* FSC_GetModuleName() {
	return Module.cName;
}

/** module handle resolver */
HINSTANCE FSC_GetModuleHandle() {
	return Module.hDLL;
}

/** flight sim window */
HWND FSC_GetFlightSimWindow() {
	return Module.hSimWindow;
}

void FSC_DisplayAtis(char* text, FSC_DisplayAtisMode mode) {

 	int i; switch (mode) {
		case FSC_ATIS_STATIC: i = 7; break;
		case FSC_ATIS_YELLOW: i = 1; break;
		case FSC_ATIS_GREEN: i = 2; break;
		case FSC_ATIS_WHITE: i = 3; break;
		default:
		case FSC_ATIS_RED: i = 6; break;
	}

	int time = 1;// don't know how time is handled - 1 is visible at least

	// a clear?
	if (text==NULL || strlen(text)==0) {
		text = "-";
		time = 0;
	}

	ImportTable.pWindowApi->DisplayAtis(text, i, time, 0);
}


/**
* Calculate the child window rectangle centered in given window according to width, height
*/
static void GetChildRect(HWND hWnd, LPRECT pRect, int width, int height) {
	GetWindowRect(Module.hSimWindow, pRect);
	pRect->left = (pRect->left+pRect->right)/2 - width/2;
	pRect->top = (pRect->bottom+pRect->top)/2 - height/2;
	pRect->right = pRect->left+width;
	pRect->bottom = pRect->top+height;
}

/**
* grab current gauge var value
*/
FLOAT64 FSC_GetNumberGaugeVar(GAUGE_TOKEN token) {

	MODULE_VAR var;
	memset(&var, 0, sizeof(var));
	var.id = token;

	ImportTable.pPanels->lookup_var(&var);

	if (var.var_type==TYPE_BCD16 || var.var_type==TYPE_BCO16)
		return (float)
		((var.var_value.d>> 0)&0xf)*   1+
		((var.var_value.d>> 4)&0xf)*  10+
		((var.var_value.d>> 8)&0xf)* 100+
		((var.var_value.d>>12)&0xf)*1000;

	return var.var_value.n;
}

BOOL FSC_GetBoolGaugeVar(GAUGE_TOKEN token) {

	MODULE_VAR var;
	memset(&var, 0, sizeof(var));
	var.id = token;

	ImportTable.pPanels->lookup_var(&var);

	return var.var_value.b;
}

VAR32   FSC_GetBCDGaugeVar(GAUGE_TOKEN token) {

	MODULE_VAR var;
	memset(&var, 0, sizeof(var));
	var.id = token;

	ImportTable.pPanels->lookup_var(&var);

	return var.var_value.d;
}

UINT32 FSC_IntToBCD(int value) {
	return
		((value%10)) |
		((value/10%10)<<4) |
		((value/100%10)<<8) |
		((value/1000%19)<<12);
}

int FSC_BCDToInt(UINT32 bcd) {
	return
		((bcd>> 0)&0xf)*   1+
		((bcd>> 4)&0xf)*  10+
		((bcd>> 8)&0xf)* 100+
		((bcd>>12)&0xf)*1000;
}

/**
 * Send a FS key event
 */
void FSC_TriggerKeyEvent(ID32 key, UINT32 value) {
	ImportTable.pPanels->trigger_key_event(key, value);
}


/**
* check for active autopilot 
*/
BOOL FSC_IsAutopilotOn() {
	return FSC_GetBoolGaugeVar(AUTOPILOT_ACTIVE)!=0;
}

/**
 * show a message dialog
 */
static LRESULT CALLBACK MessageDialogHookProc(int nCode, WPARAM wParam, LPARAM lParam) { 

	// intercept catch and patch message dialog being activated
	if (Module.hMessageWindow==0 && nCode==HCBT_ACTIVATE) {
		Module.hMessageWindow = (HWND)wParam;
		SetDlgItemText(Module.hMessageWindow, IDOK, Module.pMessageAction);
	}

	// allow continue
	return 0;
}

void FSC_ShowMessage(char* message, char* action, FSC_MessageType type)
{
	HHOOK hhook = SetWindowsHookEx(WH_CBT, MessageDialogHookProc, 0, GetCurrentThreadId());
	Module.hMessageWindow = 0;
	Module.pMessageAction = action;
	MessageBox(Module.hSimWindow, message, FSC_GetModuleName(), MB_OK | type);
	UnhookWindowsHookEx(hhook);	
	Module.hMessageWindow = 0;
}

void FSC_HideMessage() {
	HWND hwnd = Module.hMessageWindow;
	if (hwnd!=0)
		PostMessage(hwnd, WM_CLOSE, 0, 0);
}


/**
* create a menu item if it doesn't exist yet
* @param hwnd window handl
* @param path menu item path e.g. Tools|Options|Stuff
* @param id the item id or 0 for a submenu
*/
static void CreateFSMenuItem(HWND hwnd, const char* path, unsigned int id, bool checked) {

	char txt[MAX_PATH];
	MENUITEMINFO mif;

	// get main menu
	HMENU menu = GetMenu(hwnd);
	if (menu==NULL)
		return;

	// create submenus
	while (true) {
		const char* slash = strchr(path, '|');
		if (slash==NULL)
			break;

		// try to find existing menu
		HMENU submenu = 0;
		int count = GetMenuItemCount(menu);
		for (int i = 0; i<count; i++) {
			mif.cbSize = sizeof(MENUITEMINFO);
			mif.dwTypeData = txt;
			mif.cch = sizeof(txt);
			mif.fMask = MIIM_SUBMENU | MIIM_STRING | MIIM_ID;
			GetMenuItemInfo(menu, i, TRUE, &mif);
			if (strncmp(txt,path,slash-path)==0 && mif.hSubMenu!=NULL) {
				submenu = mif.hSubMenu;
				break;
			}
		}

		// create submenu now if still needed
		if (submenu==0) {
			submenu = CreateMenu();
			strncpy_s(txt, sizeof(txt), path, slash-path);
			AppendMenu(menu, MF_STRING | MF_POPUP, (UINT_PTR)submenu, txt);
		}


		// next path element
		menu = submenu;
		path = slash+1;
	}

	// check if we need final item
	mif.cbSize = sizeof(MENUITEMINFO);
	mif.dwTypeData = txt;
	mif.cch = sizeof(txt);
	mif.fMask = MIIM_ID;
	if (GetMenuItemInfo(menu, id, FALSE, &mif)) {
		// set checked on existing
		ModifyMenu(menu, id, MF_BYCOMMAND | MF_STRING | (checked ? MF_CHECKED : MF_UNCHECKED), id, path);
	} else {
		// append it
		AppendMenu(menu, MF_STRING | MF_ENABLED | (checked?MF_CHECKED:0), id, path);
	}

	// done
}

/**
* create menu items
*/
static void CreateFSMenuItems(HWND hwnd) {

	// consider menus that are set
	for (int i=0; i<FSC_MAX_MENUS; i++) {
		if (Module.menus[i].id!=0)
			CreateFSMenuItem(hwnd, Module.menus[i].path, Module.menus[i].id, Module.menus[i].checked);
	}
}


/**
 * add menu item
 */
bool FSC_AddMenu(unsigned int id, char path[], bool checked) {
	for (int i=0; i<FSC_MAX_MENUS; i++) {
		if (Module.menus[i].id==id) 
			return false;
	}

	for (int i=0; i<FSC_MAX_MENUS; i++) {
		if (Module.menus[i].id==0) {
			FSC_Log("Adding menu %s at position %d", path, i);
			strcpy_s(Module.menus[i].path, sizeof(Module.menus[i].path), path);
			Module.menus[i].checked = checked;
			Module.menus[i].id = id;
			return true;
		}
	}
	// no space
	return false;
}

/**
 * change menu item
 */
bool FSC_ChangeMenu(unsigned int id, char path[], bool checked) {
	for (int i=0; i<FSC_MAX_MENUS; i++) {
		if (Module.menus[i].id==id) {
			if (path!=NULL)
				strcpy_s(Module.menus[i].path, sizeof(Module.menus[i].path), path);
			Module.menus[i].checked = checked;
			return true;
		}
	}
	// no space
	return false;
}

/**
 * remove menu item
 */
bool FSC_RemoveMenu(unsigned int id) {
	for (int i=0; i<FSC_MAX_MENUS; i++) {
		if (Module.menus[i].id==id) {
			Module.menus[i].id = 0;
			return true;
		}
	}
	// no space
	return false;
}


/**
* Retrieve current aircraft
*/
static PFSC_AIRCRAFT GetAircraft() {
	return &Module.fscAircraft;
}


/**
 * Set timer for timer elapsed callback
 */
static VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) 
{
	FSC_CALLBACK_TimerElapsed();
}

void FSC_SetTimerCallback(int hertz) {
	if (Module.iTimer!=0)
	{
		KillTimer(NULL, Module.iTimer);
		Module.iTimer = 0;
	}
	if (hertz>0) 
		Module.iTimer = SetTimer(NULL, 0, 1000/max(10, hertz), TimerProc);
}

/*********************************************************************************
***************************** FSim callbacks & hooks *****************************
*********************************************************************************/

/**
* init the module version to match the FSim that loads this DLL
*/
static void InitModuleVersion(void) {

	// get filename of exe - fs9.exe I'd assume
	char filename[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL), filename, sizeof(filename));

	// allocate sufficient space for file version info and retrieve it
	DWORD foo;
	DWORD len = GetFileVersionInfoSize(filename, &foo);
	LPVOID buf = malloc(len);
	GetFileVersionInfo(filename, 0, len, buf);

	// lookup fixed file info from what we got
	VS_FIXEDFILEINFO* version;
	UINT verLen;
	VerQueryValue(buf, "\\", (LPVOID*)&version, &verLen);

	// set our module version accordingly
	//  VS_FIXEDFILEINFO->dwProductVersionMS - the most significant 32 bits of the binary version number
	Linkage.ModuleVersion = version->dwProductVersionMS>>8;

	// free memory again
	free(buf);
}

/**
* our window procedure that overrides the one of the simulator
*/
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
		// fs frame needs to be repainted - check that our menu is still there
		case WM_NCPAINT: 
			CreateFSMenuItems(hwnd);
			break;
		// menu choosen?
		case WM_COMMAND: 
			for (int i=0;i<FSC_MAX_MENUS;i++) {
				if (Module.menus[i].id==LOWORD(wParam)) {
					FSC_CALLBACK_MenuChosen(LOWORD(wParam));
					CreateFSMenuItems(hwnd);
					return 0;
				}
			}
			break;
	}
	// ask module implementation
	if (!FSC_CALLBACK_WindowProc(hwnd, uMsg, wParam, lParam))
		return 0;

	// continue with original
	return CallWindowProc(Module.pSimWindowProc, hwnd, uMsg, wParam, lParam);
}

/**
* our FS gauge key event handler
*/
static void FSAPI GaugeKeyEventHandler(ID32 event_id, UINT32 code, PVOID user_data) {

	// catch aircraft being loaded
	if (event_id==16 && code==96) {

		PFS_AIRCRAFT pfsAircraft = ((FS_LOADAIRCRAFT_EVENT*)user_data)->pAircraft;

		// title
		strcpy_s(Module.fscAircraft.title, sizeof(Module.fscAircraft.title), pfsAircraft->name);

		// airfile
		FSC_CalculatePath(Module.fscAircraft.airfile, sizeof(Module.fscAircraft.airfile), NULL, pfsAircraft->airfile);
		strcat_s(Module.fscAircraft.airfile, sizeof(Module.fscAircraft.airfile), ".air");

		// folder
		strcpy_s(Module.fscAircraft.folder, sizeof(Module.fscAircraft.folder), strrchr(pfsAircraft->folder, '\\')+1);

		// aircraft.cfg
		FSC_CalculatePath(Module.fscAircraft.cfgfile, sizeof(Module.fscAircraft.cfgfile), NULL, pfsAircraft->folder);
		strcat_s(Module.fscAircraft.cfgfile, sizeof(Module.fscAircraft.cfgfile), "\\aircraft.cfg");

		// notify
		FSC_CALLBACK_AircraftLoaded(&Module.fscAircraft);

	}

	// catch key events (code contains KEY_ event constant)
	if (event_id==8 && !FSC_CALLBACK_KeyEvent(code))
      return;
		
	// continue
	Module.pfsGaugeKeyEventHandler(event_id, code, user_data);
}

/**
* DLL.Main (extern "C" )
*/
BOOL APIENTRY DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {

	// reset our globals
	memset(&Module, 0, sizeof(Module));

	// remember dll handle
	Module.hDLL = hInstDLL;

	// don't need any more thread callbacks
	DisableThreadLibraryCalls(hInstDLL);

	// initialize ModuleVersion to match FSim
	InitModuleVersion();

	// all good
	return TRUE;
}

/**
* module lifecycle callbacks
*/
static void FSAPI InitModule(void) {

	char buf[MAX_PATH];

	// resolve name of module
	char path[MAX_PATH];
	GetModuleFileName(Module.hDLL, path, sizeof(path));
	char* pName = strrchr(path, '\\') + 1;
	*strrchr(path, '.') = '\0';
	strcpy_s(Module.cName, sizeof(Module.cName), pName);

	FSC_Log("InitModule");

	// hook up to window event processing
	Module.hSimWindow = FindWindow("FS98MAIN", NULL);
	if (Module.hSimWindow==NULL) {
		FSC_Log("FindWindow(\"FS98MAIN\") returned null");
		sprintf_s(buf, sizeof(buf), "FS Window NOT found - Module %s won't work", Module.cName);
		MessageBox(NULL, buf, Module.cName, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	Module.pSimWindowProc = (WNDPROC)SetWindowLong(Module.hSimWindow, GWL_WNDPROC, (LONG)WindowProc);
	if (Module.pSimWindowProc==0) {
		FSC_Log("SetWindowLong(\"handle, GWL_WNDPROC, proc\") returned null");
		sprintf_s(buf, sizeof(buf), "FS Window Hook inop - %s won't work", Module.cName);
		MessageBox(NULL, buf, Module.cName, MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	// hook into to FSim event processing (thanks to Roman on figuring out how to do that)
	Module.pfsGaugeKeyEventHandler = ImportTable.pFS9Api->pGaugeKeyEventHandler;
	ImportTable.pFS9Api->pGaugeKeyEventHandler = GaugeKeyEventHandler;

	// let module do its specifics
	FSC_CALLBACK_ModuleLoaded(Module.hSimWindow, Module.hDLL);

	// done
}

static void FSAPI DeinitModule(void) {

	// let module do its specifics
	FSC_CALLBACK_ModuleUnloaded();

	// close logfile?
	if (Module.pLogFile!=NULL)
		fclose(Module.pLogFile);

	// remove event hooks
	SetWindowLong(Module.hSimWindow, GWL_WNDPROC, (LONG)Module.pSimWindowProc);
	ImportTable.pFS9Api->pGaugeKeyEventHandler = Module.pfsGaugeKeyEventHandler;
}


/**
/*
 want to listen in on FS Key events?

  void CALLBACK HandleKeyEvents(ID32 event, UINT32 evdata, PVOID userdata) {
  }
  ImportTable.ppanel->register_key_event_handler(HandleKeyEvents, NULL);
  ImportTable.ppanel->unregister_key_event_handler(HandleKeyEvents, NULL);
*/
