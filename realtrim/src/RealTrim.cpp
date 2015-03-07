#include "RealTrim.h"
#include "FSCUtil.h"
#include "FSCJoy.h"
#include "FSCAir.h"

#include <string.h>
#include <stdio.h>

/** init state */
void realtrim_init(REALTRIM* pRealtrim) 
{
	memset(pRealtrim, 0, sizeof(REALTRIM));

	pRealtrim->trimButton = 0x0000; // the trim button 
	pRealtrim->state = FSC_ReadBoolFromProfile("Enable", true) ? IDLE : DISABLED;
	pRealtrim->startingElevatorDeflection = 0; // where we start to trim
	pRealtrim->startingTrimDeflection = 0; // where we start to trim

	// grab saved settings
	pRealtrim->trimButton = (unsigned short)FSC_ReadHexFromProfile(INI_KEY_TRIMBTN, pRealtrim->trimButton);
}

/** enabled/disable */
void realtrim_enable(REALTRIM* pRealtrim, bool enabled)
{
	FSC_WriteBoolToProfile("Enable", enabled);
	pRealtrim->state = enabled ? IDLE : DISABLED;
	FSC_Log(enabled ? "enabled" : "disabled");
}

/** reload trim characteristics for given aircraft */
void realtrim_reload(REALTRIM* pRealtrim, char* pszAirfile, char* pszConfigfile)
{
	// reset state 
	if (pRealtrim->state!=DISABLED)
		pRealtrim->state = IDLE;

	// read air file
	FSC_AIRFILE airfile;

	airfile.pElevatorTrimLimit = &pRealtrim->elevatorTrimLimit;
	airfile.pElevatorPitchMoment = &pRealtrim->elevatorPitchMoment;
	airfile.pElevatorTrimPitchMoment = &pRealtrim->elevatorTrimPitchMoment;
	airfile.nElevatorEffectivies = 7;
	airfile.pElevatorEffectivities = &pRealtrim->elevatorEffectivities[0];

	if (!FSC_ReadAirfile(pszAirfile, &airfile)) 
		FSC_Log("Couldn't read from airfile %s", pszAirfile);

	// override from aircraft.cfg file
	pRealtrim->elevatorEffectiveness = FSC_ReadDoubleFromProfile(pszConfigfile, "flight_tuning", "elevator_effectiveness", 1.0); 
	pRealtrim->elevatorTrimEffectiveness = FSC_ReadDoubleFromProfile(pszConfigfile, "flight_tuning", "elevator_trim_effectiveness", 1.0); 
	pRealtrim->elevatorTrimLimit = FSC_ReadDoubleFromProfile(pszConfigfile, "airplane_geometry", "elevator_trim_limit", pRealtrim->elevatorTrimLimit) / 360 * 2 * PI;

	// done
	FSC_Log("Changed trim variables for %s", pszAirfile);
	FSC_Log("elevator trim limit = %f rad (%.1f deg)", pRealtrim->elevatorTrimLimit, pRealtrim->elevatorTrimLimit / 2 / PI * 360);
	FSC_Log("elevator trim pitch moment = %f", pRealtrim->elevatorTrimPitchMoment);
	FSC_Log("elevator trim effectiveness = %f", pRealtrim->elevatorTrimEffectiveness);
	FSC_Log("elevator pitch moment = %f", pRealtrim->elevatorPitchMoment);
	FSC_Log("elevator effectiveness = %f", pRealtrim->elevatorEffectiveness);
	FSC_Log("elevator effectivities = ");
	FSC_Log(7, pRealtrim->elevatorEffectivities);
}

/** convert elevator deflection into moment */
double elevator_to_moment(REALTRIM* pRealtrim, double deflection)
{
 	double effectivity = FSC_Interpolate(7, pRealtrim->elevatorEffectivities, deflection);
	if (effectivity==0) effectivity = 1;

	// rad deflection * cm_de * interpolated effectivity factor * effectiveness factor
	return deflection * pRealtrim->elevatorPitchMoment * effectivity * pRealtrim->elevatorEffectiveness;
}

/** switch state to waitingforbutton */
void realtrim_getbutton(REALTRIM* pRealtrim)
{
	pRealtrim->state = WAITINGFORBUTTON;
	// show prompt
	realtrim_report(pRealtrim, "RealTrim: Press trim button on joystick");
}


/** convert trim deflection into moment */
double trim_to_moment(REALTRIM* pRealtrim, double deflection)
{
	// rad deflection * cm_dt * effectiveness factor
	return deflection * pRealtrim->elevatorTrimPitchMoment * pRealtrim->elevatorTrimEffectiveness;
}

/** trim */
void realtrim_trim(REALTRIM* pRealtrim, double elevatorDeflection, double trimDeflection, bool autopilot)
{

	// poll joystick
	FSC_PollJoysticks();

	// disabled?
	if (pRealtrim->state==DISABLED)
		return;

	// trimming?
	if (pRealtrim->state==TRIMMING) {

		// end trim via button / autopilot?
		if (autopilot || !FSC_TestButton(pRealtrim->trimButton)) {
			FSC_Log("Stopping trimming");
			pRealtrim->state = IDLE;
			return;
		}

		// calculate current elevator delta and matching trim deflection
		// calculate current elevator delta and matching trim deflection
		double startElevatorMoment = elevator_to_moment(pRealtrim, pRealtrim->startingElevatorDeflection);
		double currentElevatorMoment = elevator_to_moment(pRealtrim, elevatorDeflection);
		double deltaElevatorMoment = currentElevatorMoment - startElevatorMoment;
		double trimDelta = deltaElevatorMoment / trim_to_moment(pRealtrim, 1);

		double elevatorDelta = elevatorDeflection - pRealtrim->startingElevatorDeflection;

		double trimDeflection = pRealtrim->startingTrimDeflection - trimDelta;
		if (trimDeflection<-pRealtrim->elevatorTrimLimit) trimDeflection = -pRealtrim->elevatorTrimLimit;
		if (trimDeflection>pRealtrim->elevatorTrimLimit) trimDeflection = pRealtrim->elevatorTrimLimit;

		//apply it
		FSC_Log("Trimming %.2f degree of trim for %.2f degree of elevator deflection", (float)(trimDelta / 2 / PI * 360), (float)(elevatorDelta / 2 / PI * 360));
		realtrim_trim(pRealtrim, trimDeflection);

		return;
	}

	// waiting for button?
	if (pRealtrim->state==WAITINGFORBUTTON)
	{
FSC_Log("REMOVE:Still waiting for button");
		// button?
		int btn = FSC_TestAnyButton();
		if (btn!=FSC_NO_BUTTON) 
		{
			FSC_Log("Got trim button %d", btn);
			pRealtrim->trimButton = btn;
			FSC_WriteHexToProfile(INI_KEY_TRIMBTN, btn);

			// report result
			char button[128];
			FSC_Button2Name(button, sizeof(button), btn);
			char text[256];
			sprintf_s(text, sizeof(text), "RealTrim: Trim button is %s", button);
			realtrim_report(pRealtrim, text);

			pRealtrim->state = IDLE;
		}

		return;
	}

	// start trimming ?
	if (FSC_TestButton(pRealtrim->trimButton)) {
		// grab current inputs
		pRealtrim->startingElevatorDeflection = elevatorDeflection;
		pRealtrim->startingTrimDeflection = trimDeflection;
		FSC_Log("Start trimming with current elevator deflection %f, trim deflection %f", elevatorDeflection, trimDeflection);
		// and go
		pRealtrim->state = TRIMMING;
		return;
	}

}