#include "skybox.h"

//Global variables
GLOBAL_skybox_enum skybox_enum = {0,1,2,3,4,5};
GLuint skybox_image[6];

/*
 * Loading all the images of the skybox
 */
void initSkybox(void)
{	
	skybox_image[skybox_enum.LEFT] = texture_load("images/skybox_images/deep_lf.jpg");
	skybox_image[skybox_enum.RIGHT] = texture_load("images/skybox_images/deep_rt.jpg");
	skybox_image[skybox_enum.FRONT] = texture_load("images/skybox_images/deep_ft.jpg");
	skybox_image[skybox_enum.BACK] = texture_load("images/skybox_images/deep_bk.jpg");
	skybox_image[skybox_enum.TOP] = texture_load("images/skybox_images/deep_up.jpg");
	skybox_image[skybox_enum.BOTTOM] = texture_load("images/skybox_images/deep_dn.jpg");
}

/*
 * Drawing the quads to set the skybox images
 */
void drawSkybox(GLOBAL_Camera* camera)
{
	float pos_x = camera->centerX + 3.5f;
	float pos_y = camera->centerY + 3.5f;
	float pos_z = camera->centerZ + 3.5f;
	float neg_x = camera->centerX - 3.5f;
	float neg_y = camera->centerY - 3.5f;
	float neg_z = camera->centerZ - 3.5f;
	glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
	
	glBindTexture(GL_TEXTURE_2D, skybox_image[skybox_enum.LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(INITIAL,EXTREME);		glVertex3f(neg_x,pos_y,pos_z);
	glTexCoord2f(EXTREME,EXTREME);		glVertex3f(neg_x,pos_y,neg_z);
	glTexCoord2f(EXTREME,INITIAL);		glVertex3f(neg_x,neg_y,neg_z);
	glTexCoord2f(INITIAL,INITIAL);		glVertex3f(neg_x,neg_y,pos_z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, skybox_image[skybox_enum.RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(EXTREME,EXTREME);		glVertex3f(pos_x,pos_y,pos_z);
	glTexCoord2f(INITIAL,EXTREME);		glVertex3f(pos_x,pos_y,neg_z);
	glTexCoord2f(INITIAL,INITIAL);		glVertex3f(pos_x,neg_y,neg_z);
	glTexCoord2f(EXTREME,INITIAL);		glVertex3f(pos_x,neg_y,pos_z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, skybox_image[skybox_enum.FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(EXTREME,EXTREME);		glVertex3f(neg_x,pos_y,pos_z);
	glTexCoord2f(INITIAL,EXTREME);		glVertex3f(pos_x,pos_y,pos_z);
	glTexCoord2f(INITIAL,INITIAL);		glVertex3f(pos_x,neg_y,pos_z);
	glTexCoord2f(EXTREME,INITIAL);		glVertex3f(neg_x,neg_y,pos_z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, skybox_image[skybox_enum.BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(INITIAL,EXTREME);		glVertex3f(neg_x,pos_y,neg_z);
	glTexCoord2f(EXTREME,EXTREME);		glVertex3f(pos_x,pos_y,neg_z);
	glTexCoord2f(EXTREME,INITIAL);		glVertex3f(pos_x,neg_y,neg_z);
	glTexCoord2f(INITIAL,INITIAL);		glVertex3f(neg_x,neg_y,neg_z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, skybox_image[skybox_enum.TOP]);
	glBegin(GL_QUADS);
	glTexCoord2f(INITIAL,EXTREME);		glVertex3f(neg_x,pos_y,neg_z);
	glTexCoord2f(EXTREME,EXTREME);		glVertex3f(neg_x,pos_y,pos_z);
	glTexCoord2f(EXTREME,INITIAL);		glVertex3f(pos_x,pos_y,pos_z);
	glTexCoord2f(INITIAL,INITIAL);		glVertex3f(pos_x,pos_y,neg_z);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, skybox_image[skybox_enum.BOTTOM]);
	glBegin(GL_QUADS);
	glTexCoord2f(EXTREME,EXTREME);		glVertex3f(neg_x,neg_y,neg_z);
	glTexCoord2f(INITIAL,EXTREME);		glVertex3f(pos_x,neg_y,neg_z);
	glTexCoord2f(INITIAL,INITIAL);		glVertex3f(pos_x,neg_y,pos_z);
	glTexCoord2f(EXTREME,INITIAL);		glVertex3f(neg_x,neg_y,pos_z);
	glEnd();
	
	glPopAttrib();
    glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}