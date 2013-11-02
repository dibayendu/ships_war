#ifndef CAMERA_H
#define CAMERA_H

#include "gl.h"
#include "utility.h"

typedef struct
{
	double eyeX;
	double eyeY;
	double eyeZ;
	double centerX;
	double centerY;
	double centerZ;
	double upX;
	double upY;
	double upZ;
}GLOBAL_Camera;
extern GLOBAL_Camera camera1; /* initialised in camera.c */
extern GLOBAL_Camera camera2; /* initialised in camera.c */
extern GLOBAL_Camera initCamera1; /* initialised in camera.c */
extern GLOBAL_Camera initCamera2; /* initialised in camera.c */

void initAllCameras(void);
void displayCamera(GLOBAL_Camera*, GLOBAL_Camera*, GLOBAL_Translate*);

#endif