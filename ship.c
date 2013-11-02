#include "ship.h"

OBJMesh* mesh_1 = NULL;
OBJMesh* mesh_2 = NULL;
GLOBAL_Translate translateShip_1; /* declared in ship.h */
GLOBAL_Translate translateShip_2; /* declared in ship.h */
GLOBAL_Rotate rotateShip_1; /* declared in ship.h */
GLOBAL_Rotate rotateShip_2; /* declared in ship.h */
GLOBAL_Scale scaleShip_1; /* declared in ship.h */
GLOBAL_Scale scaleShip_2; /* declared in ship.h */
GLOBAL_MovementKeys directionKeys_ship_1; /* declared in ship.h */
GLOBAL_MovementKeys directionKeys_ship_2; /* declared in ship.h */


float speed_ship_1; /* declared in ship.h */
float speed_ship_2; /* declared in ship.h */

/* initialises all the positions and rotations of ship*/
void initAllShips(void)
{
	GLOBAL_Translate initialTranslateShip_1 = {ZERO, ZERO, SHIP_1_INTIAL_Z_POSITION}; /* declared in ship.h */
	GLOBAL_Translate initialTranslateShip_2 = {ZERO, ZERO, SHIP_2_INTIAL_Z_POSITION}; /* declared in ship.h */

	initShip(mesh_1, &directionKeys_ship_1, &initialTranslateShip_1, &translateShip_1, 
				&rotateShip_1, &scaleShip_1, &speed_ship_1, colour.red);
	initShip(mesh_2, &directionKeys_ship_1, &initialTranslateShip_2, &translateShip_2, 
				&rotateShip_2,&scaleShip_2, &speed_ship_2, colour.green);
}

/* initialises the position and rotation of one ship. */
void initShip(OBJMesh* mesh, GLOBAL_MovementKeys* directionKeys, 
				GLOBAL_Translate* initialTranslateShip, 
					GLOBAL_Translate* translateShip, GLOBAL_Rotate* rotateShip, 
						GLOBAL_Scale* scaleShip, float* speed, float colourShade[])
{
	GLOBAL_Rotate initialRotateShip = {ZERO, ZERO, ZERO}; /* declared in ship.h */
	GLOBAL_Scale initialScaleShip = {SHIP_SCALE_FACTOR, SHIP_SCALE_FACTOR, SHIP_SCALE_FACTOR}; /* declared in ship.h */
	GLOBAL_MovementKeys initialDirectionKeys = {RELEASED, RELEASED, 
		RELEASED, RELEASED};

	float initialSpeed = ZERO;

	*translateShip = *initialTranslateShip;
	*directionKeys = initialDirectionKeys;
	*rotateShip = initialRotateShip;
	*scaleShip = initialScaleShip;
	*speed = initialSpeed;
}

/* calculates and draws both the ships on the water grid. */
void drawAllShips(void)
{
	drawship(mesh_1, &translateShip_1, &rotateShip_1, &scaleShip_1, colour.red);
	drawship(mesh_2, &translateShip_2, &rotateShip_2, &scaleShip_2, colour.green);
}

/*
 * The ship object is loaded.
 */
void drawship(OBJMesh* mesh, GLOBAL_Translate* translateShip, 
			  GLOBAL_Rotate* rotateShip, GLOBAL_Scale* scaleShip, float colourShade[])
{
	glPushMatrix();
	glTranslatef(translateShip->posX, translateShip->posY + SHIP_Y_POSITION_ON_WATER, 
				 translateShip->posZ);
	
	glRotatef(rotateShip->rotX, THIS, NOT_THIS, NOT_THIS);
	glRotatef(rotateShip->rotY, NOT_THIS, THIS, NOT_THIS);
	glRotatef(rotateShip->rotZ, NOT_THIS, NOT_THIS, THIS);
	
	glScalef(scaleShip->X, scaleShip->Y, scaleShip->Z);
	
	glColor3fv(colourShade);
	mesh = objMeshLoad("galleon.obj");
	
	drawMesh(mesh);
	drawAxes();
	
	glPopMatrix();
}

/* moves both the ships */
void moveAllShips(void)
{
	moveShip(&directionKeys_ship_1, &speed_ship_1, &rotateShip_1, &translateShip_1);
	moveShip(&directionKeys_ship_2, &speed_ship_2, &rotateShip_2, &translateShip_2);
}

/*
 * Moves the ship with the events.
 */
void moveShip(GLOBAL_MovementKeys* directionKeys, float* speed, GLOBAL_Rotate* rotateShip, 
				GLOBAL_Translate* translateShip)
{
	// Increase the acceleration of the ship.
	if (directionKeys->up == PRESSED)
		*speed += STANDARD_SPEED;
	else if(directionKeys->down == PRESSED)
	{
		// Decelaration of the ship.
		if (*speed < MINIMUM_SPEED)
			*speed = NO_SPEED;
		else
			*speed -= STANDARD_SPEED;
	}
	else if(directionKeys->left == PRESSED)
	{
		// Move the ship to the left only if the ship has some speed.
		if (*speed > NO_SPEED)
		{
			rotateShip->rotY += STANDARD_ROTATION;
			if (rotateShip->rotY > MAXIMUM_ROTATION)
				rotateShip->rotY = STANDARD_ROTATION;
		}	
	}
	else if(directionKeys->right == PRESSED)
	{
		// Move the ship to the right only if the ship has some speed.
		if (*speed > NO_SPEED)
		{
			rotateShip->rotY -= STANDARD_ROTATION;
			if (rotateShip->rotY < MINIMUM_ROTATION)
				rotateShip->rotY = MAXIMUM_ROTATION - STANDARD_ROTATION;
		}
	}
	else
	{
		if (*speed < MINIMUM_SPEED)
			*speed = NO_SPEED;
		else
			*speed -= SHIP_STALLING_SPEED;
	}
	
	calculateObjectPosition(speed, rotateShip, translateShip);
}

/*
 * Calculates the motion of the ship.
 */
void calculateObjectPosition(float* speed, GLOBAL_Rotate* rotateShip, 
								GLOBAL_Translate* translateShip)
{
	float radians = rotateShip->rotY*PI/RADIANCONSTANT;
	float zPos = sinf(radians) * (*speed);
	float xPos = cosf(radians) * (*speed);
	translateShip->posX += xPos * timing.deltaTime;
	translateShip->posZ -= zPos * timing.deltaTime;
	translateShip->posY = getYAxisValue(translateShip->posX, translateShip->posZ);
	
}

/*
 * Draws the galleon/ship object
 */
void drawMesh(OBJMesh* mesh) 
{ 
	glBegin(GL_TRIANGLES); 
	for (int i = 0; i < mesh->numIndices; ++i) 
	{ 
		unsigned int index = mesh->indices[i]; 
		float* vert = (float*)((void*)mesh->vertices + 
							   index * mesh->stride); 
		float* norm = (float*)((void*)vert + mesh->normalOffset); 
		if (mesh->hasNormals) 
			glNormal3fv(norm); 
		glVertex3fv(vert); 
	} 
	glEnd(); 
}