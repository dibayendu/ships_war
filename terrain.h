#ifndef TERRAIN_H
#define TERRAIN_H

#include "gl.h"
#include "axes.h"
#include "utility.h"
#include "texture_loader_mac.h"

extern GLOBAL_Translate translate_terrain; /* initialised in terrain.c */
extern GLOBAL_Rotate rotate_terrain; /* initialised in terrain.c */

void draw_terrain(float, float, float, float, float);
void display_terrain(float, float, float, float, float);
void init_terrain(void);

#endif
