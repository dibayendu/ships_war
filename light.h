#ifndef LIGHT_H
#define LIGHT_H

#include "gl.h"
#include "utility.h"

#define WATERSHINESS 50.0f

extern GLfloat mat_ambient[4]; /* initialised in light.c */
extern GLfloat mat_specular[4]; /* initialised in light.c */
extern GLfloat light_position[4]; /* initialised in light.c */
extern GLfloat lm_ambient[4]; /* initialised in light.c */

void initLight(void);
void displayLight(void);

#endif