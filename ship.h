#ifndef SHIP_H
#define SHIP_H

#include "gl.h"
#include "waves.h"
#include "obj.h"
#include "utility.h"

#define MINIMUM_SPEED 0.000001
#define NO_SPEED 0.0f
#define STANDARD_SPEED 0.001f
#define STANDARD_ROTATION 1.0f
#define MAXIMUM_ROTATION 360.0f
#define MINIMUM_ROTATION 0.000001
#define SHIP_STALLING_SPEED 0.00001
#define SHIP_Y_POSITION_ON_WATER 0.1

#define RADIANCONSTANT 180
#define SHIP_1_INTIAL_Z_POSITION 1.0f
#define SHIP_2_INTIAL_Z_POSITION -1.0f
#define SHIP_SCALE_FACTOR 0.009f

extern GLOBAL_Translate translateShip_1; /* initialised in ship.c */
extern GLOBAL_Translate translateShip_2; /* initialised in ship.c */

extern GLOBAL_Rotate rotateShip_1; /* initialised in ship.c */
extern GLOBAL_Rotate rotateShip_2; /* initialised in ship.c */

typedef struct
{
	double X;
	double Y;
	double Z;
}GLOBAL_Scale;
extern GLOBAL_Scale scaleShip_1; /* initialised in ship.c */
extern GLOBAL_Scale scaleShip_2; /* initialised in ship.c */

typedef struct
{
	int up;
	int down;
	int left;
	int right;
}GLOBAL_MovementKeys;
extern GLOBAL_MovementKeys directionKeys_ship_1; /* initialised in ship.c */
extern GLOBAL_MovementKeys directionKeys_ship_2; /* initialised in ship.c */

extern OBJMesh* mesh_1;
extern OBJMesh* mesh_2;

extern float speed_ship_1; /* initialised in ship.c */
extern float speed_ship_2; /* initialised in ship.c */

void drawAllShips(void);
void drawship(OBJMesh*, GLOBAL_Translate*, GLOBAL_Rotate*, GLOBAL_Scale*, float[]);
void drawMesh(OBJMesh*);
void calculateObjectPosition(float*, GLOBAL_Rotate*, GLOBAL_Translate*);
void moveAllShips(void);
void moveShip(GLOBAL_MovementKeys*, float*, GLOBAL_Rotate*, GLOBAL_Translate*);
void initAllShips(void);
void initShip(OBJMesh*, GLOBAL_MovementKeys*, GLOBAL_Translate*, GLOBAL_Translate*, 
				GLOBAL_Rotate*, GLOBAL_Scale*, float*, float[]);

#endif
