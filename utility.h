#ifndef UTILITY_H
#define UTILITY_H

#include "gl.h"


#define PI 3.1415926535f
#define THIS 1.0f
#define NOT_THIS 0.0f
#define ZERO 0.0f
#define TRUE 1
#define FALSE 0
#define	TWICE 2
#define ESC 27
#define RELEASED 0
#define PRESSED 1
#define INITIAL_TEXTURE 0
#define EXTREME_TEXTURE 1

typedef struct
{
	float previousTime;
	float currentTime;
	float elapsedTime;
	float timeDivisor;
	float calculatedTime;
	float deltaTime;
}GLOBAL_RenderTime;
extern GLOBAL_RenderTime timing ; /* initialised in utility.c */

typedef struct
{
	float posX;
	float posY;
	float posZ;
}GLOBAL_Translate;

typedef struct
{
	float rotX;
	float rotY;
	float rotZ;
}GLOBAL_Rotate;

// colours are build here
typedef struct
{
	float white[3];
	float black[3];
	float red[3];
	float green[3];
	float blue[3];
	float alphaBlend[4];
}GLOBAL_Colour;
extern GLOBAL_Colour colour; /*initialised in utility.c */

// used to calculate the frame per second
typedef struct
{
	float previousTime;
	float elapsedTime;
	int frameCount;
	int fps;
}GLOBAL_FPS;
extern GLOBAL_FPS fps; /* initialised in utility.c */

void initTime(void);
void renderTime(void);
void writeTextOnScreen(float, float, char*, GLOBAL_Translate);
void calculateFPS(int);

#endif