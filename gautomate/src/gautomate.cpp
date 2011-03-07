#include "FSCModule.h"
#include "FSCUtil.h"
#include "FSCJoy.h"

#include "gauges.h"
#include <errno.h>
#include <stdio.h>

#define	MENU_ID_ENABLE 44666
#define	MENU_ID_RELOAD 44667

#define INI_KEY_ENABLED "Enabled"
#define INI_KEY_AUTOMATION "auto.%d"

#define MAX_AUTOMATIONS 256
#define AUTOMATE_BUTTON "BUTTON"
#define AUTOMATE_AXIS "AXIS"
#define AUTOMATE_KEY "KEY"

#define AUTOMATE_MOUSE_LEFTSINGLE "MOUSE_LEFTSINGLE"
#define AUTOMATE_MOUSE_MIDDLESINGLE "MOUSE_MIDDLESINGLE"
#define AUTOMATE_MOUSE_RIGHTSINGLE "MOUSE_RIGHTSINGLE"
#define AUTOMATE_MOUSE_LEFTDOUBLE "MOUSE_LEFTDOUBLE"
#define AUTOMATE_MOUSE_MIDDLEDOUBLE "MOUSE_MIDDLEDOUBLE"
#define AUTOMATE_MOUSE_RIGHTDOUBLE "MOUSE_RIGHTDOUBLE"

// gauto.x=BUTTON,jjbb,ffff,mouse,gau!gauge,x/y
// gauto.x=AXIS,jjaa,min>max,mouse,gau!gauge,x/y

struct automation_s
{
	bool (*condition)(automation_s* pautomation);
	int selector;
	float lower;
	float upper;
	int action;
	char gau[MAX_PATH];
	char gauge[MAX_PATH];
	int x;
	int y;
};

struct gautomate_s
{
	automation_s automations[MAX_AUTOMATIONS];
	bool enabled;
	char aircraft[MAX_PATH];
	int lastkey;
}
gautomate;

/**
 * automation testers
 */
bool testAutomationButton(automation_s* pautomation)
{
	return FSC_TestButton(pautomation->selector, true);
}

bool testAutomationAxis(automation_s* pautomation)
{
	return FSC_TestAxis(pautomation->selector, pautomation->lower, pautomation->upper, true);
}

bool testKeyDown(int vkkey)
{
	return (GetKeyState(vkkey) & 0x80 ) != 0;
}

bool testAutomationKey(automation_s* pautomation)
{
	int key = LOWORD(pautomation->selector);
	int modifiers = HIWORD(pautomation->selector);
	bool ctrl = (modifiers&MK_CONTROL)!=0;
	bool shift = (modifiers&MK_SHIFT)!=0;

	if (testKeyDown(key) && (ctrl==testKeyDown(VK_CONTROL)) && (shift==testKeyDown(VK_SHIFT)))
	{
		if (pautomation->lower!=0)
			return false;
		pautomation->lower = 1;
		return true;
	}

	pautomation->lower = 0;
	return false;
}

/**
 * rect calculations
 */
bool findRect(PPMOUSERECT pprect, int x, int y)
{
	int rx,ry;

	while (true)
	{
		switch ((*pprect)->rect_type)
		{
		// eol?
		case (MOUSE_RECT_EOL):
			return false;
		// parent?
		case MOUSE_RECT_PARENT: 
			rx = x-(*pprect)->relative_box.x;
			ry = y-(*pprect)->relative_box.y;
			(*pprect)++;
			if (findRect(pprect, rx, ry))
				return true;
			break; 
		case MOUSE_RECT_CHILD:
			rx = x-(*pprect)->relative_box.x;
			ry = y-(*pprect)->relative_box.y;
			if ( rx>0 && rx<(*pprect)->relative_box.size_x && ry>0 && ry<(*pprect)->relative_box.size_y )
				return true;
			(*pprect)++;
			break;
		case MOUSE_RECT_END_PARENT:
			(*pprect)++;
			return false;
		// ignore unknown
		default:
			(*pprect)++;
			break;
		}

		// next
	}
}

/**
 * Apply automation descriptors
 */
bool applyAutomation(automation_s* pautomation) 
{
	// test condition
	if (!pautomation->condition(pautomation))
		return false;

	// look for gau 
	HMODULE hgau = GetModuleHandle(pautomation->gau);
	if (hgau==NULL) 
	{
		FSC_Log("Gau %s isn't loaded", pautomation->gau);
		return false;
	}
	PGAUGESLINKAGE pgauges = (PGAUGESLINKAGE)GetProcAddress(hgau, "Linkage");
	if (pgauges==NULL)
	{
		FSC_Log("Gau %s doesn't contain Linkage", pautomation->gau);
		return false;
	}

	// find gauge 
	PGAUGEHDR pgaugeheader = NULL;
	PPGAUGEHDR ppgaugeheader = &pgauges->gauge_header_ptr[0];
	while (true) 
	{
		pgaugeheader = *ppgaugeheader;
		if (pgaugeheader==NULL || (_stricmp(pgaugeheader->gauge_name, pautomation->gauge)==NULL))
			break;
		ppgaugeheader++;
	}

	if (pgaugeheader==NULL)
	{
		FSC_Log("Gau %s doesn't contain gauge %s", pautomation->gau, pautomation->gauge);
		return false;
	}

	// find rectangle
	PMOUSERECT prect = pgaugeheader->mouse_rect;
	if (!findRect(&prect, pautomation->x, pautomation->y))
	{
		FSC_Log("Can't find rectangle for point %d/%d in gauge %s", pautomation->x, pautomation->y, pautomation->gauge);
		return false;
	}

	if (prect->mouse_function!=NULL)
	{
		FSC_Log("Apply mouse function on %s", pautomation->gauge);
		PIXPOINT pp;
		pp.x = 0;
		pp.y = 0;
		prect->mouse_function(&pp, pautomation->action);
		return true;
	}
	if (prect->event_id!=0)
	{
		FSC_Log("Apply event key on %s", pautomation->gauge);
		FSC_TriggerKeyEvent( prect->event_id, 0 );		
		return true;
	}

	FSC_Log("No mouse function for rect ont %s", pautomation->gauge);
	return false;
}



/**
 * Parse automation descriptors
 */
int parseMouse(char* pstart, char* pend)
{
	if (_strnicmp(pstart, AUTOMATE_MOUSE_LEFTSINGLE, pend-pstart)==0)
		return MOUSE_LEFTSINGLE;
	if (_strnicmp(pstart, AUTOMATE_MOUSE_MIDDLESINGLE, pend-pstart)==0)
		return MOUSE_MIDDLESINGLE;
	if (_strnicmp(pstart, AUTOMATE_MOUSE_RIGHTSINGLE, pend-pstart)==0)
		return MOUSE_RIGHTSINGLE;
	if (_strnicmp(pstart, AUTOMATE_MOUSE_LEFTDOUBLE, pend-pstart)==0)
		return MOUSE_LEFTDOUBLE;
	if (_strnicmp(pstart, AUTOMATE_MOUSE_MIDDLEDOUBLE, pend-pstart)==0)
		return MOUSE_MIDDLEDOUBLE;
	if (_strnicmp(pstart, AUTOMATE_MOUSE_RIGHTDOUBLE, pend-pstart)==0)
		return MOUSE_RIGHTDOUBLE;

	return MOUSE_NONE;
}

bool parseAutomationGauge(char* pstart, char* pend, automation_s* pautomation) 
{
	//something like: Bendix_King_Radio!Bendix-King Radio Nav-Comm 1
	char* psep = strchr(pstart, '!');
	if (psep==NULL||psep>pend)
		return false;

	strncpy_s(pautomation->gau, MAX_PATH, pstart, psep-pstart);
	strcat_s(pautomation->gau, MAX_PATH, ".gau");
	strncpy_s(pautomation->gauge, MAX_PATH, psep+1, pend-psep-1);

	return true;
}

bool parseAutomationAction(char* pcont, automation_s* pautomation)
{
	// action: MOUSE_LEFTSINGLE
	char* pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	pautomation->action = parseMouse(pcont, pseparator);
	if (pautomation->action==MOUSE_NONE)
		return false;
	pcont = pseparator+1;
	
	// x/y: 40/35
	pseparator = strchr(pcont, '/');
	if (pseparator==NULL)
		return false;
	pautomation->x = atoi(pcont);
	if (errno==ERANGE)
		return false;
	pautomation->y = atoi(pseparator+1);
	if (errno==ERANGE)
		return false;

	// good
	return true;
}

bool parseAutomationKey(char* pcont, automation_s* pautomation)
{
	//something like: Shift-S,xxxx,Bendix_King_Radio!Bendix-King Radio Nav-Comm 1,MOUSE_LEFTSINGLE,40/35

	int modifier = 0;

	// key: shift-s
	char* pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;

	char* pdash;
	while ( (pdash = strchr(pcont, '-') ) != NULL)
	{
		if (pdash>pseparator) break;

		if (_strnicmp("shift", pcont, pdash-pcont)==0)
			modifier |= MK_SHIFT;
		if (_strnicmp("ctrl", pcont, pdash-pcont)==0)
			modifier |= MK_CONTROL;

		pcont = pdash+1;
	}

	if (pcont!=pseparator-1)
	{
		FSC_Log("key binding with unknown character key");
		return false;
	}

	FSC_Log("key binding for %c", *pcont);
	pautomation->selector = MAKELONG(*pcont, modifier);

	pcont = pseparator + 1;

	// key flags: xxxx
	pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	pcont = pseparator+1;

	// gauge: Bendix_King_Radio!Bendix-King Radio Nav-Comm 1
	pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	if (!parseAutomationGauge(pcont, pseparator, pautomation))
		return false;
	pcont = pseparator+1;
	
	// action: MOUSE_LEFTSINGLE,40/35
	if (!parseAutomationAction(pcont, pautomation))
		return false;

	// condition
	pautomation->condition = testAutomationKey;

	// all good
	return true;
}

bool parseAutomationButton(char* pcont, automation_s* pautomation)
{
	//something like: jjbb,xxxx,Bendix_King_Radio!Bendix-King Radio Nav-Comm 1,MOUSE_LEFTSINGLE,40/35

	// button: 0xjjbb
	char* pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	pautomation->selector = strtol(pcont, NULL, 16);
	if (pautomation->selector<0||pautomation->selector==LONG_MAX||pautomation->selector==LONG_MIN)
		return false;
	pcont = pseparator+1;

	// button flags: xxxx
	pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	pcont = pseparator+1;

	// gauge: Bendix_King_Radio!Bendix-King Radio Nav-Comm 1
	pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	if (!parseAutomationGauge(pcont, pseparator, pautomation))
		return false;
	pcont = pseparator+1;
	
	// action: MOUSE_LEFTSINGLE,40/35
	if (!parseAutomationAction(pcont, pautomation))
		return false;

	// condition
	pautomation->condition = testAutomationButton;

	// all good
	return true;
}

bool parseAutomationAxis(char* pcont, automation_s* pautomation)
{
	// something like: AXIS,jjaa,0.0>1.0,MOUSE_LEFTSINGLE,Bendix_King_Radio!Bendix-King Radio Nav-Comm 1,40/35

	// axis: 0xjjaa
	char* pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	pautomation->selector = strtol(pcont, NULL, 16);
	if (pautomation->selector<0||pautomation->selector==LONG_MAX||pautomation->selector==LONG_MIN)
		return false;
	pcont = pseparator+1;

	// range: x.x>y.y
	pseparator = strchr(pcont, '>');
	if (pseparator==NULL)
		return false;
	pautomation->lower = (float)atof(pcont);
	if (errno==EINVAL)
		return false;
	pcont = pseparator+1;

	pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	pautomation->upper = (float)atof(pcont);
	if (errno==EINVAL)
		return false;
	pcont = pseparator+1;

	// gauge: Bendix_King_Radio!Bendix-King Radio Nav-Comm 1
	pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;
	if (!parseAutomationGauge(pcont, pseparator, pautomation))
		return false;
	pcont = pseparator+1;
	
	// action: MOUSE_LEFTSINGLE,40/35
	if (!parseAutomationAction(pcont, pautomation))
		return false;

	// condition
	pautomation->condition = testAutomationAxis;

	// all good
	return true;
}

bool parseAutomation(char* pcont, automation_s* pautomation)
{
	char* pseparator = strchr(pcont, ',');
	if (pseparator==NULL)
		return false;

	// something like: BUTTON,jjbb,xxxx,MOUSE_LEFTSINGLE,Bendix_King_Radio!Bendix-King Radio Nav-Comm 1,40/35
	if (strncmp(AUTOMATE_BUTTON, pcont, sizeof(AUTOMATE_BUTTON)-1)==0)
		return parseAutomationButton(pseparator+1, pautomation);

	// something like: AXIS,jjaa,x>y,MOUSE_LEFTSINGLE,Bendix_King_Radio!Bendix-King Radio Nav-Comm 1,40/35
	if (strncmp(AUTOMATE_AXIS, pcont, sizeof(AUTOMATE_AXIS)-1)==0)
		return parseAutomationAxis(pseparator+1, pautomation);

	// something like: KEY,key,xxxx,MOUSE_LEFTSINGLE,Bendix_King_Radio!Bendix-King Radio Nav-Comm 1,40/35
	if (strncmp(AUTOMATE_KEY, pcont, sizeof(AUTOMATE_KEY)-1)==0)
		return parseAutomationKey(pseparator+1, pautomation);

	return false;
}

void parseAutomations(char* section)
{
	char keyvalue[MAX_PATH];
	for (int k=0, a=0;;k++)
	{
		sprintf_s(keyvalue, sizeof(keyvalue), INI_KEY_AUTOMATION, k);
		FSC_ReadStringFromProfile(section, keyvalue, keyvalue, sizeof(keyvalue), "");

		if (strlen(keyvalue)==0)
			break;

		bool ok = parseAutomation(keyvalue, &gautomate.automations[a]);

		FSC_Log("Reading: %s - %s", keyvalue, (ok?"ok":"skipped"));
		if (ok) a++;

	}

}
void parseAutomations()
{
	// clear current
	memset(&gautomate.automations, 0, sizeof(&gautomate.automations));

	// loop over all global automations
	FSC_Log("Loading global automations");
	parseAutomations(NULL);

	// loop over all aircraft specific automations
	if (strlen(gautomate.aircraft)>0)
	{
		FSC_Log("Loading automations for aircraft in folder %s", gautomate.aircraft);
		parseAutomations(gautomate.aircraft);
	}

	// done
}

/**
 * menu callback
 */
void FSC_CALLBACK_MenuChosen(unsigned int id)
{
	if (id==MENU_ID_ENABLE) {
		gautomate.enabled = !gautomate.enabled;
		FSC_WriteBoolToProfile(INI_KEY_ENABLED, gautomate.enabled);
		FSC_ChangeMenu(MENU_ID_ENABLE, NULL, gautomate.enabled);
		return;
	}

	if (id==MENU_ID_RELOAD) {
		parseAutomations();
		return;
	}
}

/**
 * module initialization
 */
void FSC_CALLBACK_ModuleLoaded(HWND hFlightSimWindow, HMODULE hModule)
{
	memset(&gautomate, 0, sizeof(gautomate));

	gautomate.enabled = FSC_ReadBoolFromProfile(INI_KEY_ENABLED, true);

	// wait for aircraft loading to read automations
	//parseAutomations();

	FSC_AddMenu(MENU_ID_ENABLE, "&Modules|&Gautomate|&Enable", gautomate.enabled);
	FSC_AddMenu(MENU_ID_RELOAD, "&Modules|&Gautomate|&Reload", false);

	FSC_SetTimerCallback(20);
}

void FSC_CALLBACK_ModuleUnloaded()
{
}

/**
 * timed callback
 */
void FSC_CALLBACK_TimerElapsed()
{
	FSC_PollJoysticks();

	if (gautomate.enabled)
	{
		for (int i=0;gautomate.automations[i].condition!=NULL;i++)
			applyAutomation(&gautomate.automations[i]);

	}
}

/**
 * Handle aircraft change
 */ 
void FSC_CALLBACK_AircraftLoaded(PFSC_AIRCRAFT paircraft)
{
	strcpy_s(gautomate.aircraft, sizeof(gautomate.aircraft), paircraft->title);
	parseAutomations();
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
