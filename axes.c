#include "axes.h"

GLOBAL_Rotate rotateAxes; /* initialised in axes.c */
GLOBAL_Translate translateAxes; /* initialised in axes.c */

GLOBAL_AxesStruct axes = {FALSE, {0,0,0}, {100,0,0}, {-100,0,0},  
	{0,100,0},{0,-100,0}, {0,0,100}, {0,0,-100}, 1, 0x0101}; /*declared in axes.h*/

/*
 * Draws the notted negative axes along X, Y and Z.
 */
void drawNegativeAxes(void)
{		
	// Dotted lines for the negative sides of x,y,z
	glEnable(GL_LINE_STIPPLE); 	// Enable line stipple to use a 
	
	// Dotted stipple pattern for the lines
	glLineStipple(axes.lineStrippleFactor, axes.lineStripplePattern); 	
	glBegin(GL_LINES); 
	glColor3fv(colour.red); 	// Red for x axis
	glVertex3fv(axes.XN);
	glVertex3fv(axes.origin);
	glColor3fv(colour.green); 	// Green for y axis
	glVertex3fv(axes.origin);
	glVertex3fv(axes.YN);
	glColor3fv(colour.blue); 	// Blue for z axis
	glVertex3fv(axes.origin);
	glVertex3fv(axes.ZN);
	glEnd();
	glDisable(GL_LINE_STIPPLE);	
}

/*
 * Draws the positive continous line axes along X, Y and Z.
 */
void drawPositiveAxes(void)
{
	glBegin (GL_LINES);
	glColor3fv(colour.red); // X axis is red.
	glVertex3fv(axes.origin);
	glVertex3fv(axes.XP);
	glColor3fv(colour.green); // Y axis is green.
	glVertex3fv(axes.origin);
	glVertex3fv(axes.YP);
	glColor3fv(colour.blue); // z axis is blue.
	glVertex3fv(axes.origin);
	glVertex3fv(axes.ZP);
	glEnd();
	
}

/*
 * Draws the axes whenever the user wants it.
 */
void drawAxes(void)
{
	// Draws the axes when 'A'/'a' is clicked.
	if (axes.enabled == TRUE)
	{
		drawPositiveAxes();
		drawNegativeAxes();
	}
	glColor3fv(colour.white); // again making default colour to white..
}

/* initialising the rotation and translation of the axes with the initial value. */
void initAxes(void)
{
	GLOBAL_Rotate initRotateAxes = {0.0f, 0.0f, 0.0f};
	GLOBAL_Translate initTranslateAxes = {0.0f, 0.0f, 0.0f};
	
	rotateAxes = initRotateAxes;
	translateAxes = initTranslateAxes;
}

/* display axes in a matrix */
void displayAxes(void)
{
	glPushMatrix();
	glTranslatef(translateAxes.posX, translateAxes.posY, translateAxes.posZ); 
	glRotatef(rotateAxes.rotX, THIS, NOT_THIS, NOT_THIS);
	glRotatef(rotateAxes.rotY, NOT_THIS, THIS, NOT_THIS);
	glRotatef(rotateAxes.rotZ, NOT_THIS, NOT_THIS, THIS);
	drawAxes();
	glPopMatrix();
}