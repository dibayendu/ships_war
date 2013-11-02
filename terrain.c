#include "terrain.h"

GLOBAL_Translate translate_terrain; /* declared in terrain.h */
GLOBAL_Rotate rotate_terrain; /* declared in terrain.h */
GLuint terrain_texture;

/* loading the texture of the terrain here 
 * and initialises terrain position and rotation*/
void init_terrain(void)
{
	GLOBAL_Translate init_translate = {0.0f, 0.0f, 0.0f};
	GLOBAL_Rotate init_rotate = {0.0f, 0.0f, 0.0f};

	translate_terrain = init_translate;
	rotate_terrain = init_rotate;
	
	terrain_texture = texture_load("images/sand.jpg");
	
	if (!terrain_texture)
    {
        printf("Terrain texture cannot be loaded. Exiting!\n");
        exit(EXIT_FAILURE);
    }	
}

/*
 * Draws the quad for sand bend and texturing of the sea bed.
 */
void draw_terrain(float startPointColumn, float endPointColumn, 
				float startPointRow, float endPointRow, float depth)
{
	glBegin(GL_QUADS);
    glTexCoord2f(INITIAL_TEXTURE, EXTREME_TEXTURE);
    glVertex3f(startPointColumn, depth, startPointRow);
    glTexCoord2f(EXTREME_TEXTURE, EXTREME_TEXTURE);
    glVertex3f(endPointColumn, depth, startPointRow);
    glTexCoord2f(EXTREME_TEXTURE, INITIAL_TEXTURE);
    glVertex3f(endPointColumn, depth, endPointRow);
    glTexCoord2f(INITIAL_TEXTURE, INITIAL_TEXTURE);
    glVertex3f(startPointColumn, depth, endPointRow);
    glEnd();
}

/* this is the sea bed draw from start to end at a particular given depth. */
void display_terrain(float startPointColumn, float endPointColumn, 
					 float startPointRow, float endPointRow, float depth)
{
	glPushMatrix();

	glTranslatef(translate_terrain.posX, 
				 translate_terrain.posY, 
				 translate_terrain.posZ);
	glRotatef(rotate_terrain.rotX, THIS, NOT_THIS, NOT_THIS);
	glRotatef(rotate_terrain.rotY, NOT_THIS, THIS, NOT_THIS);
	glRotatef(rotate_terrain.rotZ, NOT_THIS, NOT_THIS, THIS);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, terrain_texture);
	
	draw_terrain(startPointColumn, endPointColumn, startPointRow, endPointRow, depth);
	drawAxes();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}