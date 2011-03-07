#include "FSCAir.h"
#include "FSCUtil.h"

#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <stdarg.h>
#include <GAUGES.h>

// see also http://www.fsdossier.info/files/aam.ini

struct CHUNK {
	unsigned long int id;
	unsigned long int len;
};

/** read bytes */
void read(FILE* handle, int chunk, int offset, void* result, int len)
{
	fseek(handle, chunk+sizeof(CHUNK)+offset, SEEK_SET);
	fread(result, len, 1, handle);
}

/** read double */
double readDouble(FILE* handle, int chunk, int offset)
{
	double result;
	fseek(handle, chunk+sizeof(CHUNK)+offset, SEEK_SET);
	fread(&result, sizeof(result), 1, handle);
	return result;
}

/** read int */
int readInt32(FILE* handle, int chunk, int offset)
{
	int result;
	fseek(handle, chunk+sizeof(CHUNK)+offset, SEEK_SET);
	fread(&result, sizeof(result), 1, handle);
	return result;
}

/** interpolate from nonlinear table of pairs - returns y */
double foo(int numPairs, double* pairs, double x)
{
	if (pairs[0]>x)
		return pairs[1];

	for (int i=1;i<numPairs;i++) {
		if (pairs[i*2+0]>x)
		{
			double x1 = pairs[i*2-2];
			double y1 = pairs[i*2-1];
			double x2 = pairs[i*2+0];
			double y2 = pairs[i*2+1];
			return y1 + (y2-y1) * ((x-x1)/(x2-x1));
		}
	}

	return pairs[numPairs*2-1];
}


/** interpolate between non linear points x,y */
double FSC_Interpolate(int numPairs, double* pairs, double x)
{
	double y = foo(numPairs, pairs, x);
	//FSC_Log("Interpolating %f = %f", x, y);
	return y;
}

/** flatten non linear function defined by points */
void FSC_Log(int numPairs, double* pairs)
{
	for (int i=0;i<numPairs;i++)
	{
		FSC_Log("(%f, %f)", pairs[i*2+0], pairs[i*2+1]);
	}
}


/** read airfile */
bool FSC_ReadAirfile(char* airFile, FSC_AIRFILE* pAirfile) 
{
	// open file
	FILE* handle;
	if (0!=fopen_s(&handle, airFile, "rb"))
		return false;

	// loop over chunk
	CHUNK chunk;

	unsigned long pos = 0;
	while (true) {

		// read next chunk
		memset(&chunk, 0x00, sizeof(chunk));
		if (fseek(handle, pos, SEEK_SET)!=0) break;
		if (fread(&chunk, sizeof(chunk), 1, handle)!=1) break;
		if (chunk.id==0x0000) break;

		//FSC_Log("Parsing air file chunk %x",chunk.id);

		switch (chunk.id)
		{
			case 0x1101:
				// AERODYNAMICS_ElEVATOR_PITCHMOMENT cm_de, int32 (Cm_de = x / 2048), per radian 
				if (pAirfile->pElevatorPitchMoment)
					*pAirfile->pElevatorPitchMoment = readInt32(handle, pos, 0x8e) / 2048.0;

				// AERODYNAMICS_TRIM_PITCHMOMENT cm_dt, double, per radian, scaled by “aircraft.cfg/elevator_trim_effectiveness”
				if (pAirfile->pElevatorTrimPitchMoment)
					*pAirfile->pElevatorTrimPitchMoment = readDouble(handle, pos, 0xAA);
				break;
			case 0x0320:
				// CONTROL_SURFACES_TRIM_LIMIT, double, radian
				if (pAirfile->pElevatorTrimLimit)
					*pAirfile->pElevatorTrimLimit = readDouble(handle, pos, 0x40);
				break;
			case 0x1541:
				// ELEVATOR_PITCHMOMENT Cm_de, double, per radian
				if (pAirfile->pElevatorPitchMoment)
					*pAirfile->pElevatorPitchMoment = readDouble(handle, pos, 0x08);
				// ELEVATOR_TRIM_PITCHMOMENT cm_de, double, per radian
				if (pAirfile->pElevatorTrimPitchMoment)
					*pAirfile->pElevatorTrimPitchMoment = readDouble(handle, pos, 0x50);
				break;
			case 0x0341:
				// elevator effectivity table (factor cm_de)
				if (pAirfile->pElevatorEffectivities)
				{
					int n = pAirfile->nElevatorEffectivies;
					pAirfile->nElevatorEffectivies = readInt32(handle, pos, 0);
					if (pAirfile->nElevatorEffectivies>n)
						FSC_Log("airfile request for up to %d pairs doesn't suffice %d pairs", n, pAirfile->nElevatorEffectivies);
					else
						read(handle, pos, 4,  pAirfile->pElevatorEffectivities, pAirfile->nElevatorEffectivies*2*sizeof(double));
				}
				break;
		}

		// next chunk
		pos += sizeof(CHUNK)+chunk.len;
	}

	// done
	fclose(handle);
	return true;
}

