#include "light.h"

GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };  /* declared in light.h */
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  /* declared in light.h */
GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };  /* declared in light.h */
GLfloat lm_ambient[] = { 0.2, 0.2, 0.2, 1.0 };  /* declared in light.h */

void initLight(void)
{
	/* nothing is done here at the moment */
}

/* light, shadows and material is drawn here. */
void displayLight(void)
{	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, WATERSHINESS);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lm_ambient);
}