#include <stdarg.h>
#include <stdio.h>
#include <windows.h>

#include "FSCUtil.h"

char* FSC_GetModuleName();

/** calculates the full pathname of given relative path */
char* FSC_CalculatePath(char* pszDest, int iDestLen, char* base, char* path)
{
	// is given path already an absolute path?
	if (strlen(path)>1 && ( path[1]==':' || strncmp(path, "\\\\", 2)==0))
	{
		strcpy_s(pszDest, iDestLen, path);
		return pszDest;
	}

	// start with base or current directory if base is not given
	if (base!=NULL)
	{
		// if base is a file then we're going to continue with its directory
		int baseLen = strlen(base);
		if ((GetFileAttributes(base)&FILE_ATTRIBUTE_DIRECTORY)==0)
			baseLen = strrchr(base, '\\') - base + 1;
		strncpy_s(pszDest, iDestLen, base, baseLen);
	}
	else 
	{
		GetCurrentDirectory((DWORD)iDestLen, (LPSTR)pszDest);
		strcat_s((LPSTR)pszDest, (DWORD)iDestLen-strlen(pszDest), (LPSTR)"\\");
	}

	// append relative path
	strcat_s((LPSTR)pszDest, (DWORD)iDestLen-strlen(pszDest), (LPSTR)path);

	// done
	return pszDest;
}


/**
 * Logging
 */
void FSC_LogVA(char* message, va_list parms) {

	static FILE* pLogFile;

#ifdef _DEBUG
	#pragma message ("*********************************************************")
	#pragma message ("*** DEBUG MODE ENABLED (logging to OutputDebugString) ***")
	#pragma message ("*********************************************************")

	char buf[4096];
	sprintf_s(buf, sizeof(buf), "%s:", FSC_GetModuleName());

	vsprintf_s(buf+strlen(buf), sizeof(buf)-strlen(buf), message, parms);
	strcat_s(buf, sizeof(buf), "\r\n"); 
	OutputDebugString(buf); 
#endif

	if (FSC_ReadBoolFromProfile("Logging", false))
	{
		if (pLogFile==NULL)
		{
			char path[MAX_PATH];
			sprintf_s(path, sizeof(path), "modules\\%s.log", FSC_GetModuleName());
			char cLogFile[MAX_PATH];
			FSC_CalculatePath(cLogFile, sizeof(cLogFile), NULL, path);
			fopen_s(&pLogFile, cLogFile, "wb");
		}
		fprintf(pLogFile, "%s:", FSC_GetModuleName());
		vfprintf(pLogFile, message, parms); 
		fwrite("\r\n", sizeof(char), 2, pLogFile); 
		FlushFileBuffers(pLogFile); 
	}
}

void FSC_Log(char* message, ... ) {
	va_list parms;
	va_start(parms, message);
	FSC_LogVA(message, parms);
	va_end(parms);
}



/**
 * ini file accessors
 */
char* IniFile() 
{
	static char cIniFile[MAX_PATH]; // ini filename

	// lazy calculation
	if (cIniFile[0]=='\0')
	{
		char path[MAX_PATH];
		sprintf_s(path, sizeof(path), "modules\\%s.ini", FSC_GetModuleName());
		char cLogFile[MAX_PATH];
		FSC_CalculatePath(cIniFile, sizeof(cLogFile), NULL, path);
	}

	// done
	return cIniFile;
}

#define ASSUME_INT(v) if (v==0 || v==LONG_MAX || v==LONG_MIN) return false;

void FSC_ReadStringFromProfile(const char* key, char* presult, int lenresult, char* fallback)
{
	FSC_ReadStringFromProfile(FSC_GetModuleName(), key, presult, lenresult, fallback);
}

void FSC_ReadStringFromProfile(const char* section, const char* key, char* presult, int lenresult, char* fallback)
{
	GetPrivateProfileString(section==NULL ? FSC_GetModuleName() : section, key, fallback, presult, lenresult, IniFile());
}

bool FSC_ReadRectFromProfile(char* iniKey, RECT* r) 
{
	char value[256];
	GetPrivateProfileString(FSC_GetModuleName(), iniKey, "", value, sizeof(value), IniFile());
	if (strlen(value)==0)
		return false;


	char* p = value;
	r->left = strtol(p, &p, 10);
	ASSUME_INT(r->left);

	r->top = strtol(++p, &p, 10);
	ASSUME_INT(r->top);

	r->right = strtol(++p, &p, 10);
	ASSUME_INT(r->right);
	r->right += r->left;

	r->bottom = strtol(++p, &p, 10);
	ASSUME_INT(r->bottom);
	r->bottom += r->top;

	// done
	return true;
}
void FSC_WriteRectToProfile(char* iniKey, RECT* r)
{
	FSC_Log("Write profile rect: %d,%d,%d,%d", r->left, r->top, r->right-r->left, r->bottom-r->top);
	char value[256];
	sprintf_s(value, sizeof(value), "%d,%d,%d,%d", r->left, r->top,  r->right-r->left, r->bottom-r->top);
	WritePrivateProfileString(FSC_GetModuleName(), iniKey, value, IniFile());
}

long FSC_ReadHexFromProfile(char* iniKey, long fallback) 
{
	char buf[16];
	GetPrivateProfileString(FSC_GetModuleName(), iniKey, "", buf, sizeof(buf), IniFile());
	if (strlen(buf)==0)
		return fallback;
	long result = strtol(buf, NULL, 16);
	FSC_Log("Read profile: %s = %s(%d)", iniKey, buf, result); 
	return result;
}

void FSC_WriteHexToProfile(char* iniKey, UWORD hex) {
	char buf[16];
	sprintf_s(buf, sizeof(buf), "%04x", hex);
	WritePrivateProfileString(FSC_GetModuleName(), iniKey, buf, IniFile());
}

bool FSC_ReadBoolFromProfile(char* iniKey, bool fallback) {
	return GetPrivateProfileInt(FSC_GetModuleName(), iniKey, fallback ? 1 : 0, IniFile()) != 0;
}

int FSC_ReadIntFromProfile(char* iniKey, int fallback) {
	return GetPrivateProfileInt(FSC_GetModuleName(), iniKey, fallback, IniFile());
}

void FSC_WriteIntToProfile(char* iniKey, int value)
{
	char buf[16+1];
	sprintf_s(buf, sizeof(buf), "%d", value);
	WritePrivateProfileString(FSC_GetModuleName(), iniKey, buf, IniFile());
}

void FSC_WriteBoolToProfile(char* iniKey, bool value) 
{
	WritePrivateProfileString(FSC_GetModuleName(), iniKey, value ? "1" : "0", IniFile());
}

double FSC_ReadDoubleFromProfile(const char* pfile, const char* section, const char* key, double fallback) 
{
	char buf[16];
	GetPrivateProfileString(section, key, "", buf, sizeof(buf), pfile);
	double result = strtod(buf, NULL);
	return result == 0 ? fallback : result;
}
double FSC_ReadDoubleFromProfile(const char* section, const char* key, double fallback) 
{
	return FSC_ReadDoubleFromProfile(IniFile(), section, key, fallback);
}

void FSC_WriteDoubleToProfile(const char* pfile, const char* section, const char* key, double value) 
{
	char buf[16+1];
	sprintf_s(buf, sizeof(buf), "%.2f", value);
	WritePrivateProfileString(section, key, buf, pfile);
}
void FSC_WriteDoubleToProfile(const char* section, const char* key, double value) 
{
	FSC_WriteDoubleToProfile(IniFile(), section, key, value);
}


