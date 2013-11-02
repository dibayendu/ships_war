#ifndef CANNON_H
#define CANNON_H

#include "gl.h"
#include "ship.h"

#define INITIAL_SHOT_VELOCITY 10
#define TOTAL_CANNON_SHOTS 100
#define SHOT_NOT_FIRED 0
#define SHOT_FIRED 1
#define SHOT_NOT_DROWNED 0
#define SHOT_DROWNED 1
#define LEFT_CANNON 90.0f
#define RIGHT_CANNON -90.0f
#define VELOCITY_OF_GRAVITY 9.8f
#define SHOT_RADIUS 0.02f
#define SHOT_SLICES 8 
#define SHOT_STACKS 4
#define SHOT_CHANGE_OF_TIME_CONSTANT 0.1f
#define HALF 0.5
#define SEA_BED -0.3f

typedef struct
{
	double X;
	double Y;
	double Z;
}GLOBAL_Velocity;

typedef struct
{
	GLOBAL_Velocity shotVelocity;
	GLOBAL_Velocity deltaVelocity;
	GLOBAL_Translate translateShot;
	int fired;
	int drowned;
	float radianShot;
}GLOBAL_CANNON_SHOT;

extern GLOBAL_CANNON_SHOT cannon_shots_ship_1[TOTAL_CANNON_SHOTS]; /* initialised in cannon.c*/
extern GLOBAL_CANNON_SHOT cannon_shots_ship_2[TOTAL_CANNON_SHOTS]; /* initialised in cannon.c*/
extern GLOBAL_Velocity gravity; /* initialised in cannon.c*/
extern int shots_left_ship_1; /* initialised in cannon.c*/
extern int shots_left_ship_2; /* initialised in cannon.c*/

void initialiseShotsOfAllShips(void);
void initialiseAllShots(GLOBAL_CANNON_SHOT*, int*);
void initShot(GLOBAL_CANNON_SHOT*, int, GLOBAL_Velocity*, GLOBAL_Velocity*, GLOBAL_Translate*);

void displayAllShots(GLOBAL_CANNON_SHOT*, int*);
void displayShot(int i, GLOBAL_CANNON_SHOT*);
void displayShotsOfAllShips(void);

void moveAllCannonShots(GLOBAL_CANNON_SHOT*, int, GLOBAL_Translate*);
void moveCanonShot(int, GLOBAL_CANNON_SHOT*, GLOBAL_Translate*);
void moveShotAlongWithShip(int, GLOBAL_CANNON_SHOT*, GLOBAL_Translate*);
void moveShotsOfAllShips(void);

void fireCannon(float, GLOBAL_CANNON_SHOT*, int*, GLOBAL_Rotate*);
int getCannonShotNumber(GLOBAL_CANNON_SHOT*, int*);

#endif