// realtrim's constants
#define PI 3.1415926535897932384626433832795

#define INI_KEY_FREQUENCY "TrimFrequency"
#define INI_KEY_TRIMBTN "TrimButton"
#define INI_KEY_ADJUSTTRIMINC "AdjustTrimIncrements"
#define INI_KEY_TRIMWITHMWHEEL "TrimWithMouseWheel"
#define INI_KEY_LOGGING "Logging"

enum STATE
{
	DISABLED,
	IDLE,
	TRIMMING,
	WAITINGFORBUTTON
};

// realtrim's state
struct REALTRIM
{

	unsigned short trimButton; // the trim button 

	STATE state;
	double startingElevatorDeflection; // where we start to trim
	double startingTrimDeflection; // where we start to trim

	double elevatorTrimLimit;
	double elevatorEffectiveness;
	double elevatorTrimEffectiveness;
	double elevatorTrimPitchMoment;
	double elevatorPitchMoment;

	double elevatorEffectivities[7*2];

};

// forwards
void realtrim_init(REALTRIM* pRealtrim);
void realtrim_reload(REALTRIM* pRealtrim, char* pszAirfile, char* pszConfigfile);
void realtrim_trim(REALTRIM* pRealtrim, double elevatorDeflection, double trimDeflection, bool autopilot);
void realtrim_trim(REALTRIM* pRealtrim, double trimDeflection);
void realtrim_getbutton(REALTRIM* pRealtrim);
void realtrim_report(REALTRIM* pRealtrim, char* msg);
void realtrim_enable(REALTRIM* pRealtrim, bool enabled);