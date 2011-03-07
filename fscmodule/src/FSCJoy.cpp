/**
* FSCModule - a Flight Simulator FS2004/X module skeleton
* Copyright (c) 2006-2008, Nils Meier
*/

/*********************************************************************************
**************************** includes/dependencies *******************************
*********************************************************************************/

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <stdio.h>

#include "FSCJoy.h"
#include "FSCUtil.h"

/*********************************************************************************
************************************ forwards ************************************
*********************************************************************************/
HINSTANCE FSC_GetModuleHandle();
HWND FSC_GetFlightSimWindow();

/*********************************************************************************
******************************** global variables *******************************
*********************************************************************************/

struct {
	int num;
	char jName[FSC_MAX_JOYSTICKS][256];
	IDirectInputDevice* pJoystick[FSC_MAX_JOYSTICKS];
	DIJOYSTATE2 currentState[FSC_MAX_JOYSTICKS];
	DIJOYSTATE2 lastState[FSC_MAX_JOYSTICKS];
} DirectInput = { -1 };

/*********************************************************************************
********************************** implementation ********************************
*********************************************************************************/

/**
 * directx init callback
 */
static BOOL FAR PASCAL DirectInputInitLoop(LPCDIDEVICEINSTANCEA pDevice, LPVOID pUserData) {

	FSC_Log("Found Joystick %s", pDevice->tszInstanceName);

	LPDIRECTINPUT pDirectInput = (LPDIRECTINPUT)pUserData;

	// try to grab device/joystick
	if (FAILED(pDirectInput->CreateDevice(pDevice->guidInstance, &DirectInput.pJoystick[DirectInput.num], NULL))) {
		FSC_Log("DirectInputInit:CreateDevice failed");
		return DIENUM_CONTINUE;
	}

	// initialize for reading
	if (FAILED(DirectInput.pJoystick[DirectInput.num]->SetDataFormat(&c_dfDIJoystick2))) {
		FSC_Log("DirectInputInit:SetDataFormat failed");
		return DIENUM_CONTINUE;
	}

	if (FAILED(DirectInput.pJoystick[DirectInput.num]->SetCooperativeLevel(FSC_GetFlightSimWindow(), DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) {
		FSC_Log("DirectInputInit:SetCooperativeLevel failed");
		return DIENUM_CONTINUE;
	}

	// grab name
	strcpy_s(DirectInput.jName[DirectInput.num], sizeof(DirectInput.jName[DirectInput.num]), pDevice->tszInstanceName);

	// init properties
	DIPROPRANGE diprg;
	diprg.diph.dwSize		= sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
	diprg.diph.dwHow		= DIPH_BYOFFSET;
	diprg.lMax				= FSC_AXIS_MAX;
	diprg.lMin				= FSC_AXIS_MIN;

	DWORD axiss[] = {DIJOFS_X, DIJOFS_Y,DIJOFS_Z,DIJOFS_RX,DIJOFS_RY,DIJOFS_RZ,DIJOFS_SLIDER(0),DIJOFS_SLIDER(1),-1};

	for (int i=0;axiss[i]!=-1;i++)
	{
		diprg.diph.dwObj = axiss[i];
		DirectInput.pJoystick[DirectInput.num]->SetProperty(DIPROP_RANGE, &diprg.diph);
	}

	// keep
	DirectInput.num++;

	// done
	return DirectInput.num == FSC_MAX_JOYSTICKS ? DIENUM_STOP : DIENUM_CONTINUE;
}

/**
 * directx input initialization
 */
static void DirectInputInit() {

	if (DirectInput.num>=0)
		return;


	// reset direct input info we've got
	memset(&DirectInput, 0x00, sizeof(DirectInput));

	// connect to dinput
	LPDIRECTINPUT pDirectInput; 
	if (FAILED(DirectInput8Create(FSC_GetModuleHandle(), DIRECTINPUT_VERSION, IID_IDirectInput8A, (LPVOID*) &pDirectInput, NULL))) {
 		FSC_Log("DirectInputInit:DirectInputCreate failed");
 		return;
 	}

	// find joysticks DI8DEVCLASS_GAMECTRL DI8DEVTYPE_JOYSTICK
	pDirectInput->EnumDevices(DI8DEVCLASS_GAMECTRL, &DirectInputInitLoop, pDirectInput, DIEDFL_ATTACHEDONLY);
	if (DirectInput.num==0) 
		FSC_Log("DirectInputInit:No Joystick found");

	// done
}

/**
 * poll directx state of joystick
 */
static bool DirectInputPollJoystick(int joy) {
	// ensure initialized
	DirectInputInit();
	// valid argument?
	if (joy>=DirectInput.num)
		return false;
	// poll now
	if (FAILED(DirectInput.pJoystick[joy]->GetDeviceState(sizeof(DIJOYSTATE2), &DirectInput.currentState[joy]))) {
		if (FAILED(DirectInput.pJoystick[joy]->Acquire()))
			FSC_Log("Couldn't read device state and then Re-aquire Joystick");
		return false;
	}
	// done
	return true;
}

/**
* captures last state for capturing toggle (push/release)
*/
void FSC_PollJoysticks() {

	DirectInputInit();

	memcpy(&DirectInput.lastState, &DirectInput.currentState, sizeof(DirectInput.lastState)); 
	for (int i=0; i<DirectInput.num; i++) {
		if (!DirectInputPollJoystick(i))
			memcpy(&DirectInput.currentState[i], &DirectInput.lastState[i], sizeof(DIJOYSTATE2));
	}
}

/**
 * checks for joustick axis in range
 */
bool FSC_TestAxis(unsigned int axis, float lower, float upper, bool is_toggle)
{
	// valid?
	if (axis==FSC_NO_AXIS)
		return false;
	// disect into joystick and axis
	BYTE joy = HIBYTE(axis);
	BYTE axs = LOBYTE(axis);
	// good arguments?
	if (joy>=DirectInput.num)
		return false;
	if (axs>=8)
		return false;
	// check axis
	long* current = &DirectInput.currentState[joy].lX;

	long* last = &DirectInput.lastState[joy].lX;

	long min = (long)(lower*FSC_AXIS_MAX - FSC_AXIS_MIN);
	long max = (long)(upper*FSC_AXIS_MAX - FSC_AXIS_MIN);

	bool is = min <= current[axs] && current[axs] < max;
	bool was = min <= last[axs] && last[axs] < max;
	
	return (!is_toggle||!was) && is;
}

/**
 * checks for button press by index 
 * @param button 
 * @result true if pressed
 */
bool FSC_TestButton(unsigned int button, bool is_toggle)
{
	// valid?
	if (button==FSC_NO_BUTTON)
		return false;
	// disect into joystick and button
	BYTE joy = HIBYTE(button);
	BYTE btn = LOBYTE(button);
	// good arguments?
	if (joy>=DirectInput.num)
		return false;
	if (btn>=128)
		return false;
	// check button
	return (!is_toggle||DirectInput.lastState[joy].rgbButtons[btn]==0) && (DirectInput.currentState[joy].rgbButtons[btn]!=0);
}
bool FSC_TestButton(unsigned int button) {
	return FSC_TestButton(button, false);
}

/**
* names a button
*/
void FSC_Button2Name(char* dest, int destlen, unsigned int button) {

	BYTE joy = HIBYTE(button);
	BYTE btn = LOBYTE(button);

	if (button==FSC_NO_BUTTON || joy >= DirectInput.num) 
		return;

	sprintf_s(dest, destlen, "Button #%d, %s", btn, DirectInput.jName[joy]);

}

/**
* checks for any button press
* @result button
*/
unsigned int FSC_TestAnyButton() {
	// loop over joysticks
	for (UCHAR joy=0;joy<DirectInput.num;joy++) {
		// loop over all available buttons
		for (UCHAR btn=0;btn<128;btn++) {
			if (DirectInput.lastState[joy].rgbButtons[btn]==0&&DirectInput.currentState[joy].rgbButtons[btn]!=0) {
				FSC_Log("Poll for any button found joy #%d button #%d (0x%.4x)", joy, btn, MAKEWORD(btn,joy));
				return MAKEWORD(btn,joy);
			}
		}
		// next
	}
	// nothing found
	return FSC_NO_BUTTON;
}

