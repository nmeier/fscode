#include "Ctrl.h"
#include "FSCUtil.h"
#include "FSCJoy.h"
#include "FSCAir.h"

#include <string.h>
#include <stdio.h>

void ctrl_init(CTRL* ctrl) 
{
	memset(ctrl, 0, sizeof(CTRL));
}

void ctrl_timer(CTRL* ctrl) 
{

	FSC_PollJoysticks();

	// Obviously this is totally hardcoded atm and is supposed to come from ctrl.ini
	// It's the 2nd joystick, 2nd axis, split into half up/down atm
	int gear = 1;
	if (FSC_TestAxis(0x0101, 0.0, 0.5, false))
		gear = 0;

	ctrl_set_gear(ctrl, gear);
}

