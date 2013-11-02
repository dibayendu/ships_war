#include "keys.h"


/* initialising all the keys of both the ships movement. */
void initAllKeys(void)
{
	// no key needs to be initialised at the moment.
}

/* this function is to move the first ship */
void shipMovementKeys(GLOBAL_MovementKeys* directionKeys, int key, int state)
{
	switch (key) 
	{
		case GLUT_KEY_UP:
			directionKeys->up = state;
			break;
		case GLUT_KEY_DOWN:
			directionKeys->down = state;
			break;
		case GLUT_KEY_LEFT:
			directionKeys->left = state;
			break;
		case GLUT_KEY_RIGHT:
			directionKeys->right = state;
			break;
		default:
			break;
	}
}

/* this function is to move the second ship. */
void secondShipKeys(unsigned char key, int state)
{
	switch(key)
	{
		case 'w':
		case 'W':
			shipMovementKeys(&directionKeys_ship_2, GLUT_KEY_UP, state);
			break;
		case 'a':
		case 'A':
			shipMovementKeys(&directionKeys_ship_2, GLUT_KEY_LEFT, state);
			break;
		case 's':
		case 'S':
			shipMovementKeys(&directionKeys_ship_2, GLUT_KEY_DOWN, state);
			break;
		case 'd':
		case 'D':
			shipMovementKeys(&directionKeys_ship_2, GLUT_KEY_RIGHT, state);
			break;
	}
}

/* This is the main keyboard function. */
void keyboardKeys(unsigned char key)
{
	switch(key)
	{
		case 'w':
		case 'W':
		case 'a':
		case 'A':
		case 's':
		case 'S':
		case 'd':
		case 'D':
			secondShipKeys(key, PRESSED);
			break;
		case 'x':
		case 'X':
			// Enable or disable axis
			if (axes.enabled == FALSE)
				axes.enabled = TRUE;
			else
				axes.enabled = FALSE;
			break;
		case 'f':
		case 'F':
			// Enable or disable wireframe
			if(waves.polygonMode == GL_FILL)
				waves.polygonMode = GL_LINE;
			else
				waves.polygonMode = GL_FILL;
			break;
		case '>':
			timing.timeDivisor *= HALF;
			break;
		case '<':
			timing.timeDivisor *= TWICE;
			break;
		case '-':
			// Decrease tessellation
			waves.rows *= HALF;
			waves.cols *= HALF;
			if(waves.cols < 1)
				waves.cols = 1;
			if(waves.rows < 1)
				waves.rows = 1;
			break;
		case '+':
			// Increase tessellation
			waves.rows *= TWICE;
			waves.cols *= TWICE;
			break;
		case 'N':
		case 'n':
			// Enable or disable normals of water.
			if (normalDraw.linesEnabled == TRUE)
				normalDraw.linesEnabled = FALSE;
			else
				normalDraw.linesEnabled = TRUE;
			break;
		case 'o':
		case 'O':
			// enable or disable lighting and shadows.
			if (normalDraw.shadowsEnabled == TRUE)
				normalDraw.shadowsEnabled = FALSE;
			else
				normalDraw.shadowsEnabled = TRUE;
			break;
		case 'p':
		case 'P':
			speed_ship_1 = NO_SPEED;  // special brake to stop the ship from moving. 
			speed_ship_2 = NO_SPEED;  // special brake to stop the ship from moving. 
			break;
		case 'j':
			waves.scaleFactor += WAVE_HEIGHT;
			if (waves.scaleFactor > MAXIMUM_WAVE_HEIGHT)
				waves.scaleFactor = MAXIMUM_WAVE_HEIGHT;
			break;
		case 'k':
			waves.scaleFactor -= WAVE_HEIGHT;
			if (waves.scaleFactor < MINIMUM_WAVE_HEIGHT)
				waves.scaleFactor = MINIMUM_WAVE_HEIGHT;
			break;
		case '9':
			fireCannon(LEFT_CANNON, &cannon_shots_ship_1[0], &shots_left_ship_1, &rotateShip_1);
			break;
		case '0':
			fireCannon(RIGHT_CANNON, &cannon_shots_ship_1[0], &shots_left_ship_1, &rotateShip_1);
			break;
		case '5':
			fireCannon(LEFT_CANNON, &cannon_shots_ship_2[0], &shots_left_ship_2, &rotateShip_2);
			break;
		case '6':
			fireCannon(RIGHT_CANNON, &cannon_shots_ship_2[0], &shots_left_ship_2, &rotateShip_2);
			break;
			
		case (char)ESC:
			exit(EXIT_SUCCESS);
			break;
	}
}
