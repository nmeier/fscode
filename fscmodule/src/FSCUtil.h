#include "windows.h"

/**
 * Misc file operations
 */
char* FSC_CalculatePath(char* absolutePath, int lenAbsolutePath, char* base, char* path);

/**
 * Log a message to log file or debug out
 */
void FSC_Log(char* message, ... );
void FSC_LogVA(char* message, va_list parms);

/** 
 * profile functions
 */
void FSC_ReadStringFromProfile(const char* key, char* presult, int lenresult, char* fallback);
void FSC_ReadStringFromProfile(const char* section, const char* key, char* presult, int lenresult, char* fallback);
long FSC_ReadHexFromProfile(char* iniKey, long fallback);
bool FSC_ReadBoolFromProfile(char* iniKey, bool fallback);
int  FSC_ReadIntFromProfile(char* iniKey, int fallback);
bool FSC_ReadRectFromProfile(char* iniKey, RECT* r);
double FSC_ReadDoubleFromProfile(const char* file, const char* section, const char* key, double fallback);
double FSC_ReadDoubleFromProfile(const char* section, const char* key, double fallback);

void FSC_WriteHexToProfile(char* iniKey, UWORD hex);
void FSC_WriteBoolToProfile(char* iniKey, bool value);
void FSC_WriteRectToProfile(char* iniKey, RECT* r);
void FSC_WriteDoubleToProfile(const char* pfile, const char* section, const char* key, double value); 
void FSC_WriteDoubleToProfile(const char* section, const char* key, double value); 
