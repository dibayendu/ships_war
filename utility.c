#include "utility.h"

//global variables
GLOBAL_RenderTime timing; /* declared in utility.h*/
GLOBAL_Colour colour = {{1,1,1}, {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1}, {1, 1, 1, 0.7f}}; /*declared in utility.h*/
GLOBAL_FPS fps = {0.0f, 0.0f, 0, 0}; /* declared in utility.h*/

/*
 * Used for calculating the time between the frames and when idle.
 */
void renderTime(void)
{
	// Get the time when the previous frame was rendered
	timing.previousTime = timing.currentTime;
	
	// Get the current time (in milliseconds) and calculate the elapsed time
	timing.currentTime = glutGet(GLUT_ELAPSED_TIME);
	timing.elapsedTime = timing.currentTime - timing.previousTime;
	timing.deltaTime = timing.elapsedTime / timing.timeDivisor;
	timing.calculatedTime += timing.deltaTime;
}

/* initialising the time calculation */
void initTime(void)
{
	GLOBAL_RenderTime initialTiming = {0.0f, 0.0f, 0.0f, 5000.0f, 0.0f, 0.0f};
	timing = initialTiming;
}

/* printing the string on the screen at x, y position and moves along with camera. */
void writeTextOnScreen(float x, float y, char* string, GLOBAL_Translate translateShip)
{
	char *c;
	
	glColor3fv(colour.green);
	glRasterPos3f(x + translateShip.posX, y, translateShip.posZ);
	
	//Move until unless the end character is found.
	for (c=string; *c != '\0'; c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	glColor3fv(colour.white);
}

/* frame per second is calculated in the method below.*/
void calculateFPS(int currentTime)
{
    fps.frameCount++;
    int timeInterval = currentTime - fps.previousTime;
	
    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps.fps = fps.frameCount / (timeInterval / 1000.0f);
        fps.previousTime = currentTime;
		
		// frame count is reset after a second has passed.
        fps.frameCount = 0;
    }
}