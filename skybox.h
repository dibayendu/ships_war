#ifndef SKYBOX_H
#define SKYBOX_H

#include "gl.h"
#include "texture_loader_mac.h"
#include "camera.h"

#define INITIAL 0.0005
#define EXTREME 0.9995

typedef struct
{
	int LEFT;
	int RIGHT;
	int FRONT;
	int BACK;
	int TOP;
	int BOTTOM;
}GLOBAL_skybox_enum;

void initSkybox(void);
void drawSkybox(GLOBAL_Camera* camera);

#endif
