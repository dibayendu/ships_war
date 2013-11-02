#include "camera.h"

GLOBAL_Camera camera1; /* declared in camera.h */
GLOBAL_Camera camera2; /* declared in camera.h */
GLOBAL_Camera initCamera1; /* declared in camera.h */
GLOBAL_Camera initCamera2;  /* declared in camera.h */

/* initialising both the cameras with the default values. */
void initAllCameras(void)
{
	GLOBAL_Camera preInitCamera1 = {0.0, 1.0, 3.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
	initCamera1 = preInitCamera1;
	camera1 = initCamera1;
	
	GLOBAL_Camera preInitCamera2 = {0.0, 1.0, -3.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
	initCamera2 = preInitCamera2;
	camera2 = initCamera2;
}

void displayCamera(GLOBAL_Camera* initCamera, GLOBAL_Camera* camera, GLOBAL_Translate* translateShip)
{
	camera->eyeX = initCamera->eyeX + translateShip->posX;
	camera->eyeZ = initCamera->eyeZ + translateShip->posZ;
	camera->centerX = initCamera->centerX + translateShip->posX;
	camera->centerZ = initCamera->centerZ + translateShip->posZ;
	gluLookAt(camera->eyeX, 
			  camera->eyeY, 
			  camera->eyeZ, 
			  camera->centerX, 
			  camera->centerY,
			  camera->centerZ, 
			  camera->upX, 
			  camera->upY, 
			  camera->upZ);	
}