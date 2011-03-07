#define FSC_NO_BUTTON 0xffff
#define FSC_NO_AXIS 0xffff
#define FSC_MAX_JOYSTICKS 8
#define FSC_AXIS_MAX 1000
#define FSC_AXIS_MIN 0

/** poll joysticks */
void FSC_PollJoysticks();

/** check button pressed */
bool FSC_TestButton(unsigned int button);

/** check button pressed if previously released */
bool FSC_TestButton(unsigned int button, bool is_toggle);

/** wait for any button */
unsigned int FSC_TestAnyButton();

/** check axis range */
bool FSC_TestAxis(unsigned int axis, float lower, float upper, bool is_toggle);

/** convert button to name */
void FSC_Button2Name(char* dest, int destlen, unsigned int button);


