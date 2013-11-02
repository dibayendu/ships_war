#ifndef AXES_H
#define AXES_H

#include "gl.h"
#include "utility.h"

typedef struct
{
	int enabled;
	float origin[3];
	float XP[3];
	float XN[3];
	float YP[3];
	float YN[3];
	float ZP[3];
	float ZN[3];
	int lineStrippleFactor;
	unsigned short lineStripplePattern;
}GLOBAL_AxesStruct;
extern GLOBAL_AxesStruct axes; /*initialised in axes.c*/

extern GLOBAL_Rotate rotateAxes; /* initialised in axes.c */
extern GLOBAL_Translate translateAxes; /* initialised in axes.c */

void drawPositiveAxes(void);
void drawNegativeAxes(void);
void drawAxes(void);
void initAxes(void);
void displayAxes(void);

#endif