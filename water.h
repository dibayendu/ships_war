#ifndef WATER_H
#define WATER_H

// All the declarations here.
#include "gl.h"
#include "texture_loader_mac.h"
#include "skybox.h"
#include "axes.h"
#include "waves.h"
#include "ship.h"
#include "cannon.h"
#include "utility.h"
#include "keys.h"
#include "camera.h"
#include "light.h"
#include "collision_detector.h"
#include "terrain.h"
#include "particle_system.h"
#include "terrain_perlin_noise.h"
#include "perlin_noise_own.h"

#define INITIALX 0
#define INITIALY 0
#define DARKEST 0.0f
#define BRIGHTEST 1.0f
#define STANDARD_MOUSE_ROTATION 1.0f
#define LEFT_BUTTON 0
#define RIGHT_BUTTON 2
#define CLICKED 0
#define NOT_CLICKED 1
#define ROTATEWORLD_DIVISOR 5.0
#define ZOOM_DIVISOR 50.0
#define MINIMUM_ZOOM -3.0
#define MAXIMUM_ZOOM 10.0
#define MAIN_FUNCTION_ARGUMENTS 3


// All the structs defined here
typedef struct
{
	double fovy;
	double aspect;
	double zNear;
	double zFar;
}GLOBAL_Perspective;
GLOBAL_Perspective perspective = {75.0, 0.0, 0.01, 100.0};

extern GLOBAL_Translate translateWorld; /* initialised in water.c */
extern GLOBAL_Rotate rotateWorld; /* initialised in water.c */

//global variable
int leftClicked = NOT_CLICKED;
int rightClicked = NOT_CLICKED;

int previousWorldXPosition = 0;
int previousWorldYPosition = 0;

// function declarations
void initWorld(void);
void idle(void);
void reshape(int, int);
void display(void);
void keyboardFunc(unsigned char, int, int);
void keyboardUpFunc(unsigned char, int, int);
void mouseFunc(int, int, int, int);
void motionFunc(int, int);
void initialise_all(void);
void displayObjects(void);
void specialKeysFunc(int, int, int);
void specialUpKeysFunc(int, int, int);
void displayWorld(void);

#endif