#include "FSCUtil.h"
#include "FSCJoy.h"
#include "FSCModuleX.h"

#include "RealTrim.h"

/** consts */
static enum EVENT_ID{
	EVENT_MENU,
	EVENT_MENU_BUTTON,
	EVENT_MENU_ENABLE,
	EVENT_MENU_DISABLE,
    EVENT_AIRCRAFTLOADED,
	EVENT_TIMER,
	EVENT_TEXT
};

static enum REQUEST_ID {
	REQUEST_DATA,
	REQUEST_AIRCRAFT
};

static enum DEFINITION_ID {
	DEFINE_REQUEST,
	DEFINE_SET
};

struct DATA_REQUEST {
	double trimDeflection;
	double elevatorDeflection;
	bool autopilot;
};

struct DATA_SET {
	double trimDeflection;
};

struct REALTRIMX : public REALTRIM
{
	HANDLE hSim;
};

/** state */
REALTRIMX realtrim;

/** callback - dispatch*/
void FSC_CALLBACK_DispatchProc(HANDLE hSim, SIMCONNECT_RECV* pRecv)
{
	// aircraft chang event
	SIMCONNECT_RECV_(EVENT_FILENAME, pFilename, pRecv);
	if (pFilename && pFilename->uEventID == EVENT_AIRCRAFTLOADED)
	{
		FSC_Log("Aircraft changed: %s", pFilename->szFileName);
		char configfile[MAX_PATH];
		FSC_CalculatePath(configfile, sizeof(configfile), pFilename->szFileName, "aircraft.cfg");
		realtrim_reload(&realtrim, pFilename->szFileName, configfile);
	}

	// aircraft request delivered
	SIMCONNECT_RECV_(SYSTEM_STATE, pState, pRecv);
	if (pState && pState->dwRequestID == REQUEST_AIRCRAFT)
	{
		FSC_Log("Aircraft is: %s", pState->szString);
		char configfile[MAX_PATH];
		FSC_CalculatePath(configfile, sizeof(configfile), pState->szString, "aircraft.cfg");
		realtrim_reload(&realtrim, pState->szString, configfile);
	}

	// requested data being delivered - once per sim frame
	SIMCONNECT_RECV_(SIMOBJECT_DATA, pClient, pRecv);
	if (pClient)
	{
		// trim it
		DATA_REQUEST* pData = (DATA_REQUEST*)&pClient->dwData;
		realtrim_trim(&realtrim, pData->elevatorDeflection, pData->trimDeflection, pData->autopilot);
	}

	// menu chosen
	SIMCONNECT_RECV_(EVENT, pEvent, pRecv);
	if (pEvent) switch (pEvent->uEventID)
	{
		case EVENT_MENU_ENABLE:
			SimConnect_MenuDeleteSubItem(hSim, EVENT_MENU, EVENT_MENU_ENABLE);
			SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "Disable", EVENT_MENU_DISABLE, 0);
			realtrim_enable(&realtrim, true);
			break;
		case EVENT_MENU_DISABLE:
			SimConnect_MenuDeleteSubItem(hSim, EVENT_MENU, EVENT_MENU_DISABLE);
			SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "Enable", EVENT_MENU_ENABLE, 0);
			realtrim_enable(&realtrim, false);
			break;
		case EVENT_MENU_BUTTON:
			realtrim_getbutton(&realtrim);
			break;
	}

	// done
}

/** realtrim message reporting callback */
void realtrim_report(REALTRIM* pRealtrim, char* message)
{
	SimConnect_Text(realtrim.hSim, SIMCONNECT_TEXT_TYPE_SCROLL_WHITE, 30, EVENT_TEXT, strlen(message)+1, message);
}

/** callback - module up */
void FSC_CALLBACK_ModuleLoaded(HANDLE hSim) 
{

	FSC_Log("Loading Realtrim");

	// init state
	realtrim_init(&realtrim);

	realtrim.hSim = hSim;

	// add a menu entry
	SimConnect_MenuAddItem(hSim, "&RealTrim", EVENT_MENU, 0);
	SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "Trim &Button...", EVENT_MENU_BUTTON, 0);
	if (realtrim.state!=DISABLED)
		SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "&Disable", EVENT_MENU_DISABLE, 0);
	else
		SimConnect_MenuAddSubItem(hSim, EVENT_MENU, "&Enable", EVENT_MENU_ENABLE, 0);

	// listen to aircraft load event and sim frame
	SimConnect_SubscribeToSystemEvent(hSim, EVENT_AIRCRAFTLOADED, "AircraftLoaded");

	// prepare out data definitions
	SimConnect_AddToDataDefinition(hSim, DEFINE_REQUEST, "ELEVATOR TRIM POSITION", "Radians"); //Elevator trim deflection (angle)
	SimConnect_AddToDataDefinition(hSim, DEFINE_REQUEST, "ELEVATOR DEFLECTION", "Radians"); //Elevator deflection (angle)
	SimConnect_AddToDataDefinition(hSim, DEFINE_REQUEST, "AUTOPILOT MASTER", "Bool", SIMCONNECT_DATATYPE_INT32);

	SimConnect_AddToDataDefinition(hSim, DEFINE_SET    , "ELEVATOR TRIM POSITION", "Radians");

	// request data once per sim frame 
	SimConnect_RequestDataOnSimObject(hSim, REQUEST_DATA, DEFINE_REQUEST, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME);

	// request current aircraft
	SimConnect_RequestSystemState(hSim, REQUEST_AIRCRAFT, "AircraftLoaded");
}

/** callback - module down */
void FSC_CALLBACK_ModuleUnloaded(HANDLE hSim)
{
	FSC_Log("Unloading Realtrim");
}

/** implementation for setting trim */
void realtrim_trim(REALTRIM* pRealtrim, double trimDeflection)
{
	// in FSX ELEVATOR TRIM POSITION actually means "Elevator trim deflection in radians"
	DATA_SET set;
	set.trimDeflection = trimDeflection;
	SimConnect_SetDataOnSimObject(realtrim.hSim, DEFINE_SET, SIMCONNECT_OBJECT_ID_USER, 0, 1, sizeof(double), &set);
}

