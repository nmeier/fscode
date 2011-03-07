
#ifndef	__AIRFILE_H__
#define __AIRFILE_H__

struct FSC_AIRFILE {

	// 0x0320, 0x40
	double* pElevatorTrimLimit;

	// cm_de 0x1101, 0x8e & 0x1541, 0x08
	double* pElevatorPitchMoment;

	// cm_dt 0x1101, 0xAA
	double* pElevatorTrimPitchMoment;

	// 0x341, scales the Elevator Pitch Moment cm_de, n pairs stored in p
	// X = Elevator deflection angle (radian)
	// Y = Pitch moment multiplier
	// Don Simon: "Control surface effectiveness is linear in effect with deflection up to a critical angle 
	// of approximately 12 deg. After the critical angle flow separation occurs and the control surface 
	// effectiveness reduces. Thus, the "y" value should be set to 1 until the "x" value where separation 
	// occurs, with reductions beyond that." 
	// For many FS stock aircraft the effectivity is a straight line at 1.0. This means the elevator effectivity 
	// doesn't change with deflection. The effectivity table of some others is more realistic and resemble the 
	// shape of a bell: the efficiency is at low deflection degrees = 1 and decreases tu =0 at big deflection 
	// angles. Other aircraft use inverted effectivity: The effectivity is at lower deflection angle very low 
	// (near 0) and increases to = 1 at big deflection angle. The table shows then a "V". This smooth the effect of the elevator. 
	int nElevatorEffectivies;
	double* pElevatorEffectivities;

};

bool FSC_ReadAirfile(char* file, FSC_AIRFILE* pAirfile);

double FSC_Interpolate(int numPairs, double* pairs, double x);	

void FSC_Log(int numPairs, double* pairs);


#endif