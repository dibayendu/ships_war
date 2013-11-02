#include "water.h"

GLOBAL_Translate translateWorld; /* declared in water.h */
GLOBAL_Rotate rotateWorld; /* declared in water.h */

int width;
int height;
int draw;
int game_over;
/***********************************************************************************
******************************* ALL EVENT HANDLERS *********************************
************************************************************************************/

/*
 * When mouse button pressed and moved.
 */
void motionFunc(int x, int y)
{
	if (leftClicked == CLICKED)
	{
		rotateWorld.rotX += (y - previousWorldYPosition) / ROTATEWORLD_DIVISOR;
		rotateWorld.rotY += (x - previousWorldXPosition) / ROTATEWORLD_DIVISOR;
		glutPostRedisplay ();
	}
	else if (rightClicked == CLICKED)
	{
		rotateWorld.rotX += (x - previousWorldXPosition) / ROTATEWORLD_DIVISOR;
		translateWorld.posZ += (previousWorldYPosition - y) / ZOOM_DIVISOR;
		if (translateWorld.posZ < MINIMUM_ZOOM)
			translateWorld.posZ = MINIMUM_ZOOM;
		if (translateWorld.posZ > MAXIMUM_ZOOM)
			translateWorld.posZ = MAXIMUM_ZOOM;
		glutPostRedisplay ();
	}
	
	previousWorldXPosition = x;
	previousWorldYPosition = y;
	glutPostRedisplay();
	
}

/*
 * When mouse button is pressed.
 */
void mouseFunc(int button, int state, int x, int y)
{	
	if (button == LEFT_BUTTON)
		leftClicked = state;
	else if (button == RIGHT_BUTTON)
		rightClicked = state;
	
	previousWorldXPosition = x;
	previousWorldYPosition = y;
	glutPostRedisplay();
}

/*
 * Keyboard functions to call all the events.
 */
void keyboardFunc(unsigned char key, int x, int y)
{
	if(game_over && key == '~')
		initialise_all();
	else if(key == 27)
		exit(EXIT_SUCCESS);
	else if(!game_over)
		keyboardKeys(key);
}

/*
 * releasing movement keys of second ship
 */
void keyboardUpFunc(unsigned char key, int x, int y)
{
	if(!game_over)
		secondShipKeys(key, RELEASED);
}

/* This is the special function for the directional keys*/
void specialKeysFunc(int key, int x, int y)
{	
	if(!game_over)
		shipMovementKeys(&directionKeys_ship_1, key, PRESSED);
}

/* This is the special function for the directional keys*/
void specialUpKeysFunc(int key, int x, int y)
{
	if(!game_over)
		shipMovementKeys(&directionKeys_ship_1, key, RELEASED);
}

/*#################################################################################*/

/*
 * Resizes and re-shapes the window.
 
 void reshape(int w, int h)
 {
 perspective.aspect = w / (float)h;
 
 // NOTE: initial value of x,y = 0,0
 glViewport(INITIALX, INITIALY, w, h);		
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(perspective.fovy, perspective.aspect, 
 perspective.zNear, perspective.zFar);
 glMatrixMode(GL_MODELVIEW);
 
 }
 */
 
 /*
 * This is the functions which redraws for every frame and the main display function;
 
void display(void)
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	displayWorld();
	glutSwapBuffers();
}
*/

/*
 * Resizes and re-shapes the window.
 */
void reshape(int w, int h)
{
	//width = w;
	//height = h;
	width = glutGet(GLUT_WINDOW_WIDTH); height = glutGet(GLUT_WINDOW_HEIGHT);
	glutPostRedisplay();
}

/* diplays lives left, shots left and the fps on the screen infront of the camera. */
void show_game_details(int shots_left_ship, int lives_left, GLOBAL_Translate translate_ship)
{
	char buffer[100] = "fps = ";
	char fps_buffer[10];
	sprintf(fps_buffer, "%d", fps.fps);
	strcat(buffer, fps_buffer);
	
	char buffer_2[100] = "Shots left = ";
	char shot_buffer[10];
	sprintf(shot_buffer, "%d", shots_left_ship);
	strcat(buffer_2, shot_buffer);
	
	char buffer_3[100] = "Lives Left = ";
	char lives_buffer[10];
	sprintf(lives_buffer, "%d", lives_left);
	strcat(buffer_3, lives_buffer);
	
	writeTextOnScreen(0.0, 1.27, buffer, translate_ship);
	writeTextOnScreen(0.0, 1.19, buffer_2, translate_ship);
	writeTextOnScreen(0.0, 1.11, buffer_3, translate_ship);
}

/* checks if game is over and lets users know about it. */
void check_for_game_over(float screen_x_position, int lives_left, GLOBAL_Translate translate_ship)
{
	if (game_over) 
	{
		if (draw)
		{
			char b3[100] = "SHIPS COLLIDED. GAME DRAW! Press ~ to restart.";
			writeTextOnScreen(screen_x_position, 1.0f, b3, translate_ship);
		}
		else 
		{
			if (lives_left >= 1) {
				char b3[100] = "YOU WIN. GAME OVER! Press ~ to restart.";
				writeTextOnScreen(screen_x_position, 1.0f, b3, translate_ship);
			}
			else {
				char b3[100] = "YOU LOST. GAME OVER! Press ~ to restart.";
				writeTextOnScreen(screen_x_position, 1.0f, b3, translate_ship);
			}
		}
	}
}

/* displays each of the viewports for the ship. */
void view_view_port(float viewport_x_pos, int viewport_width, int viewport_height, GLOBAL_Camera* initCamera,
					GLOBAL_Camera* camera, GLOBAL_Translate* translate_ship, 
					int player_lives, int shots_left, float screen_x_pos)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(viewport_x_pos, 0, (float)viewport_width/2 , viewport_height);
	gluPerspective(45, ((float)viewport_width/2)/(viewport_height), 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glScissor(viewport_x_pos, 0, viewport_width/2 , viewport_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	// there is lights camera and action with all the worldly objects.
	displayLight();
	displayCamera(initCamera, camera, translate_ship);
	drawSkybox(camera);
	displayWorld();
	show_game_details(shots_left, player_lives, *translate_ship);
 	check_for_game_over(screen_x_pos, player_lives, *translate_ship);
	
	//draw_particle_system_scene(translateShip_1.posX, translateShip_1.posY, translateShip_1.posZ, 
	//						   TRUE, rotateWorld.rotX, rotateWorld.rotY);
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); 
	glPushMatrix();
	glPopMatrix();
	glPopAttrib();
	
}

/*
 * This is the functions which redraws for every frame and the main display function;
 */
void display(void)
{	
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_DEPTH_TEST);
	
	/* LEFT VIEW PORT */
	view_view_port(0.0f, width, height, &initCamera2, &camera2, 
					&translateShip_2, player_2_lives, shots_left_ship_2, 1.0f);
	
	/* THE SECOND VIEW PORT */
	view_view_port((float)width/2, width, height, &initCamera1, &camera1, 
					&translateShip_1, player_1_lives, shots_left_ship_1, -1.0f);
	
	glDisable(GL_SCISSOR_TEST);
	glFlush();
	glutSwapBuffers();
	
}

/* displays the world around the camera */
void displayWorld(void)
{
	//displayLight();
	//displayCamera(&initCamera1, &camera1, &translateShip_1);
	
	glPushMatrix();
	glTranslatef(translateWorld.posX, translateWorld.posY, translateWorld.posZ);
	glRotatef(rotateWorld.rotX, THIS, NOT_THIS, NOT_THIS);
	glRotatef(rotateWorld.rotY, NOT_THIS, THIS, NOT_THIS);
	glRotatef(rotateWorld.rotZ, NOT_THIS, NOT_THIS, THIS);
	displayObjects();
	glPopMatrix();	
}

/*
 * Dislays all the objects in the world
 */
void displayObjects(void)
{
	//displayLight();
	//displayCamera(&initCamera1, &camera1, &translateShip_1);

	//drawSkybox(&camera1);
	displayAxes();
/*	display_terrain(waves.startPointColumn,
					waves.endPointColumn,
					waves.startPointRow,
					waves.endPointRow,
					waves.seaBedDepth);
 */
/*	draw_perlin_noise_terrain(-6.0,
							  6.0f,
							  -6.0f,
							  6.0,
							  0.1f);
*/
//	display_personal_perlin_noise(waves.startPointRow, waves.endPointRow,
//								   waves.startPointColumn, waves.endPointColumn, waves.counter,
//								   rotateWorld, translateWorld, waves.seaBedDepth);
	
	drawAllShips();
	display_waves();
	displayShotsOfAllShips();
}

/* checks if ships have collided or have been hit by cannon shots from another ship. */
void check_ship_collision_and_damage()
{
	int ships_collided = shipsCollided(&translateShip_1, &translateShip_2);
	if (ships_collided) 
	{
		draw = TRUE;
		game_over = TRUE;
		printf("\nShips Collided.");
	}
	
	if (!game_over) 
	{
		player_1_lives = shipDamaged(player_1_lives, &translateShip_1, cannon_shots_ship_2);
		if (player_1_lives <1)
			game_over = TRUE;
		else 
		{
			player_2_lives = shipDamaged(player_2_lives, &translateShip_2, cannon_shots_ship_1);
			if (player_2_lives < 1) 
				game_over = TRUE;
		}
	}
}

/*
 * This funciton is called when ever the application is idle.
 */
void idle(void)
{
	renderTime();
	calculateFPS(timing.currentTime);
	if(!game_over)
	{
		moveAllShips();
		moveShotsOfAllShips();
		advance_particles(timing.deltaTime);
 		check_ship_collision_and_damage();
	}
	glutPostRedisplay();
	
}

/* setting up the translation and rotation vector of the initial world. */
void initWorld(void)
{
	GLOBAL_Translate initialTranslateWorld = {0.0f, 0.0f, 0.0f};
	GLOBAL_Rotate initialRotateWorld = {0.0f, 0.0f, 0.0f};
	
	translateWorld = initialTranslateWorld;
	rotateWorld = initialRotateWorld;
}

/*
 * Initialise the whole applicaiton.
 */
void initialise_all(void)
{	
	draw = FALSE;
	game_over = FALSE;
	initAllCameras();
	initTime();
	initAllKeys();
	initAxes();
	initGrid();
	initialise_terrain_perlin_noise_own();
//	init_terrain();
//	initialise_perlin_noise_terrain();
	initAllShips();
	initialiseShotsOfAllShips();
	initPlayers();
	initSkybox();
	initLight();
	initWorld();
//	initialise_particle_system();
	
	glClearAccum(DARKEST, DARKEST, DARKEST, DARKEST);
	
	timing.currentTime = glutGet(GLUT_ELAPSED_TIME);
}

/*
 * main function to run the application.
 */
int main(int argc, char **argv)
{
	srand((unsigned int)time(0));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	width = glutGet(GLUT_SCREEN_WIDTH); 
	height = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowSize(width, height);
	glutCreateWindow("Assignment 2 (Interactive 3D and Graphics Animation)");
	initialise_all();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutKeyboardFunc(keyboardFunc);
	glutKeyboardUpFunc(keyboardUpFunc);
	glutSpecialFunc(specialKeysFunc);
	glutSpecialUpFunc(specialUpKeysFunc);
	
	initialise_particle_system_engine();	// it starts to do the step to move paritcle at initialise
	
	glutMainLoop();
	
	return EXIT_SUCCESS;
}
