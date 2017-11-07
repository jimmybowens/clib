#ifndef COM_VINCY_APPS_OUTPUT_H
#define COM_VINCY_APPS_OUTPUT_H 
#include <clib/string.h>


void startColorProgram(void);
void stopColorProgram(void);
int colorProgramRunning(void);
int colorProgramValidate ( string *param );
void colorizeString ( char *value );
void colorizeInt ( int value, char endTerm);
void colorizeLong ( long  value, char endTerm);
void colorizeLongLong ( long long value, char endTerm);
#endif
