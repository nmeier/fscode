#include <windows.h>
#include <GAUGES.h>

/**
 * Definitions
 */
typedef struct {
	char folder[MAX_PATH];
	char title[MAX_PATH];
	char airfile[MAX_PATH];
	char cfgfile[MAX_PATH];
} FSC_AIRCRAFT, *PFSC_AIRCRAFT;

#define FSC_DEFAULT_IDLE_FREQUENCY 20 // 20hz (20 times a second)
#define FSC_MAX_MENUS 8

/** module handle */
HINSTANCE FSC_GetModuleHandle();

/** module name */
char* FSC_GetModuleName();

/** flight sim window */
HWND FSC_GetFlightSimWindow();

/**
* check for active autopilot 
*/
BOOL FSC_IsAutopilotOn();

/**
 * show message in dialog
 */
enum FSC_MessageType { FSC_MSG_INFO = MB_ICONINFORMATION, FSC_MSG_QUESTION = MB_ICONQUESTION, FSC_MSG_ERROR = MB_ICONERROR };

void FSC_ShowMessage(char* message, char* action, FSC_MessageType type);

void FSC_HideMessage();

/**
 * show atis message
 */
enum FSC_DisplayAtisMode { FSC_ATIS_NONE, FSC_ATIS_STATIC, FSC_ATIS_YELLOW, FSC_ATIS_GREEN, FSC_ATIS_WHITE, FSC_ATIS_RED };

void FSC_DisplayAtis(char* text, FSC_DisplayAtisMode mode);

/**
 * Lookup a gauge token value
 */
FLOAT64 FSC_GetNumberGaugeVar(GAUGE_TOKEN token);
VAR32   FSC_GetBCDGaugeVar(GAUGE_TOKEN token);
BOOL    FSC_GetBoolGaugeVar(GAUGE_TOKEN token);

/**
 * gauge var type conversions
 */
UINT32 FSC_IntToBCD(int value);
int FSC_BCDToInt(UINT32 bcd);

/**
 * Send a FS key event
 */
void FSC_TriggerKeyEvent(ID32 key, UINT32 value);

/**
 * Set timer for timer elapsed callback
 */
void FSC_SetTimerCallback(int hertz);

/**
 * add menu item
 */
bool FSC_AddMenu(unsigned int id, char path[], bool checked);

/**
 * change menu item
 */
bool FSC_ChangeMenu(unsigned int id, char path[], bool checked);

/**
 * remove menu item
 */
bool FSC_RemoveMenu(unsigned int id);

// Callbacks to be defined in module

/**
 * menu callback
 */
void FSC_CALLBACK_MenuChosen(unsigned int id);

/**
 * module initialization
 */
void FSC_CALLBACK_ModuleLoaded(HWND hFlightSimWindow, HMODULE hModule);
void FSC_CALLBACK_ModuleUnloaded();

/**
 * timed callback
 */
void FSC_CALLBACK_TimerElapsed();

/**
 * Handle aircraft change
 */ 
void FSC_CALLBACK_AircraftLoaded(PFSC_AIRCRAFT);

/**
 * Handle windows event
 */
bool FSC_CALLBACK_WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
 * Handle FS Key Event (KEY_ID_MIN++)
 * @return true if event can continue to FS, false otherwise
 */
bool FSC_CALLBACK_KeyEvent(ID32 key);
