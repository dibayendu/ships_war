#include "cannon.h"

GLOBAL_Velocity gravity = {ZERO,  -VELOCITY_OF_GRAVITY, ZERO}; /*declared in cannon.h*/
GLOBAL_CANNON_SHOT cannon_shots_ship_1[TOTAL_CANNON_SHOTS]; /*declared in cannon.h*/
GLOBAL_CANNON_SHOT cannon_shots_ship_2[TOTAL_CANNON_SHOTS]; /*declared in cannon.h*/

int shots_left_ship_1; /*declared in cannon.h*/
int shots_left_ship_2; /*declared in cannon.h*/

/* initialises all the shots of all the ships*/
void initialiseShotsOfAllShips(void)
{
	initialiseAllShots(&cannon_shots_ship_1[0], &shots_left_ship_1);
	initialiseAllShots(&cannon_shots_ship_2[0], &shots_left_ship_2);
}

/* sets the initial position of all the shots*/
void initialiseAllShots(GLOBAL_CANNON_SHOT* cannon_shots, int* shots_left)
{
	GLOBAL_Velocity initialShotVelocity = {INITIAL_SHOT_VELOCITY, 
											INITIAL_SHOT_VELOCITY, 
												INITIAL_SHOT_VELOCITY};
	GLOBAL_Velocity initialDeltaVelocity = {ZERO,  ZERO, ZERO};
	GLOBAL_Translate initialTranslateShot = {ZERO, ZERO, ZERO};
	
	*shots_left = TOTAL_CANNON_SHOTS;
	int i= 0;
	for( i = 0; i < TOTAL_CANNON_SHOTS; i++)
	{
		initShot(cannon_shots, i, &initialShotVelocity, &initialDeltaVelocity, 
					&initialTranslateShot);
	}
}

/* Initialise shot will initial position of the ship.
 * In the wireframe view, looks like ship has the cannons.
 */
void initShot(GLOBAL_CANNON_SHOT* cannon_shots, int i, GLOBAL_Velocity* initialShotVelocity, 
				GLOBAL_Velocity* initialDeltaVelocity, GLOBAL_Translate* initialTranslateShot)
{
	cannon_shots[i].shotVelocity = *initialShotVelocity;
	cannon_shots[i].deltaVelocity = *initialDeltaVelocity;
	cannon_shots[i].translateShot = *initialTranslateShot;
	cannon_shots[i].fired = SHOT_NOT_FIRED;
	cannon_shots[i].drowned = SHOT_NOT_DROWNED;
	cannon_shots[i].radianShot = ZERO;
}

/* displays shots of all the ships. */
void displayShotsOfAllShips(void)
{
	displayAllShots(&cannon_shots_ship_1[0], &shots_left_ship_1);
	displayAllShots(&cannon_shots_ship_2[0], &shots_left_ship_2);
}

/* displays all the shots in the cannon. */
void displayAllShots(GLOBAL_CANNON_SHOT* cannon_shots, int* shots_left)
{
	/* When no shots are fired or all shots fired and drowned, do nothing */
	if (*shots_left == TOTAL_CANNON_SHOTS || 
			(*shots_left < 1 && cannon_shots[TOTAL_CANNON_SHOTS - 1].drowned)) 
				return; 
	
	int i= 0;
	for( i = 0; i < TOTAL_CANNON_SHOTS; i++)
	{
		displayShot(i, cannon_shots);
	}
}

/*
 * displays only position of one shot
 */
void displayShot(int i, GLOBAL_CANNON_SHOT* cannon_shots)
{
	
	glPushMatrix();
	glTranslatef(cannon_shots[i].translateShot.posX, 
				 cannon_shots[i].translateShot.posY + SHIP_Y_POSITION_ON_WATER, 
				 cannon_shots[i].translateShot.posZ);
	glColor3fv(colour.red);
	glutSolidSphere(SHOT_RADIUS, SHOT_SLICES, SHOT_STACKS);
	drawAxes();
	glPopMatrix();
}

/* moves all the cannon shots from all the ships */
void moveShotsOfAllShips(void)
{
	moveAllCannonShots(&cannon_shots_ship_1[0], shots_left_ship_1, &translateShip_1);
	moveAllCannonShots(&cannon_shots_ship_2[0], shots_left_ship_2, &translateShip_2);
}

/* translates positions of all the cannon shots when fired. */
void moveAllCannonShots(GLOBAL_CANNON_SHOT* cannon_shots, int shots_left, 
								GLOBAL_Translate* translateShip)
{
		/* When no shots are fired or all shots fired and drowned, do nothing */
	if (shots_left < 1 && cannon_shots[TOTAL_CANNON_SHOTS - 1].drowned)
			return;
	
	int i= 0;
	for( i = 0; i < TOTAL_CANNON_SHOTS; i++)
	{
		moveCanonShot(i, cannon_shots, translateShip);
	}
}

/*
 * translates the position of the cannon shot through physics.
 */
void moveCanonShot(int i, GLOBAL_CANNON_SHOT* cannon_shots, GLOBAL_Translate* translateShip)
{
	if (cannon_shots[i].fired && !cannon_shots[i].drowned)
	{
		//calculates the co-ordinates of the cannon ball when fired
		float zPos = sinf(cannon_shots[i].radianShot) * cannon_shots[i].shotVelocity.Z;
		float xPos = cosf(cannon_shots[i].radianShot) * cannon_shots[i].shotVelocity.X;
		cannon_shots[i].deltaVelocity.Y = gravity.Y * timing.deltaTime;
		cannon_shots[i].translateShot.posX += xPos * timing.deltaTime*SHOT_CHANGE_OF_TIME_CONSTANT;
		cannon_shots[i].translateShot.posZ -= zPos * timing.deltaTime*SHOT_CHANGE_OF_TIME_CONSTANT;
		cannon_shots[i].translateShot.posY += (cannon_shots[i].shotVelocity.Y
												+ cannon_shots[i].deltaVelocity.Y * HALF)
														* timing.deltaTime
															* SHOT_CHANGE_OF_TIME_CONSTANT;
		cannon_shots[i].shotVelocity.Y += cannon_shots[i].deltaVelocity.Y;
		
		// if the ball is below the sea bed, put it drowned, so that co-ordinates are not updated
		if (cannon_shots[i].translateShot.posY < SEA_BED)
		{
			cannon_shots[i].drowned = SHOT_DROWNED;
		}
	}
	else 
	{
		moveShotAlongWithShip(i, cannon_shots, translateShip);
	}
}

/* moves the cannon shot along with the ship. */
void moveShotAlongWithShip(int i, GLOBAL_CANNON_SHOT* cannon_shots, 
										GLOBAL_Translate* translateShip)
{
	cannon_shots[i].translateShot.posX = translateShip->posX;
	cannon_shots[i].translateShot.posY = translateShip->posY + SHIP_Y_POSITION_ON_WATER;
	cannon_shots[i].translateShot.posZ = translateShip->posZ;
	cannon_shots[i].shotVelocity.X = INITIAL_SHOT_VELOCITY;
	cannon_shots[i].shotVelocity.Y = INITIAL_SHOT_VELOCITY;
	cannon_shots[i].shotVelocity.Y = INITIAL_SHOT_VELOCITY;
}

/* determines which shot number is fired from cannon and fires it*/
void fireCannon(float shotRotation, GLOBAL_CANNON_SHOT* cannon_shots, int* shots_left, 
				GLOBAL_Rotate* rotateShip)
{
	int shot_number = getCannonShotNumber(cannon_shots, shots_left);
	if (shot_number < 0) /* -1 means there are no shots in the cannon. */
		return;
	
	cannon_shots[shot_number].fired = SHOT_FIRED;
	cannon_shots[shot_number].radianShot = (rotateShip->rotY + shotRotation)*PI/RADIANCONSTANT;
}

/* determines what is the number of the shot the cannon has fired. */
int getCannonShotNumber(GLOBAL_CANNON_SHOT* cannon_shots, int* shots_left)
{
	int i= 0;
	for( i = 0; i < TOTAL_CANNON_SHOTS; i++)
	{
		if (cannon_shots[i].fired == SHOT_NOT_FIRED) 
		{
			printf("Total Shots left = %d\n", --(*shots_left));
			return i;
		}
	}	
	
	return -1; /* -1 means there are no shots in the cannon. */
}