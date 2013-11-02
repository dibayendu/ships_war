#include "particle_system.h"

GLuint texture;
Particle particles[NUM_PARTICLES];
float timeUntilNextStep;

//The color of particles that the fountain is currently shooting.  0
//indicates red, and when it reaches 1, it starts over at red again.  It
//always lies between 0 and 1.
float colorTime;
//The angle at which the fountain is shooting particles, in radians.
float angle;		

//Returns a random float from 0 to < 1
float randomFloat() {
	return (float)rand() / ((float)RAND_MAX + 1);
}

/* calculates what colour the particle should be depending upon the position of the particle. */
void calculate_colour(float* x,float* y, float* z)
{			
	if (colorTime < 0.166667f) {
		*x = 1.0f; *y = colorTime * 6; *z = 0.0f;
	}
	else if (colorTime < 0.333333f) {
		*x = (0.333333f-colorTime) * 6; *y = 1.0f; *z = 0.0f;
	}
	else if (colorTime < 0.5f) {
		*x = 0.0f; *y = 1.0f; *z = (colorTime - 0.333333f) * 6;
	}
	else if (colorTime < 0.666667f) {
		*x = 0.0f; *y = (0.666667f - colorTime) * 6; *z = 1.0f;
	}
	else if (colorTime < 0.833333f) {
		*x = (colorTime - 0.666667f) * 6; *y = 0.0f; *z = 1.0f;
	}
	else {
		*x = 1.0f; *y = 0.0f; *z = ((1.0f - colorTime) * 6);
	}
	
	//Make sure each of the color's components range from 0 to 1
	if(*x < 0)
		*x = 0;
	if(*y < 0)
		*y = 0;
	if(*z < 0)
		*z = 0; 
	
	if(*x > 1)
		*x = 1;
	if(*y > 1)
		*y = 1;
	if(*z > 1)
		*z = 1;
}

/* sets up the initial velocity of the particle and the lifespan and time_alive.  */
void create_particle(Particle* p)
{
	p->posX = 0; p->posY = 0; p->posZ = 0;
	
	p->velX = 2 * cos(angle) + (0.5f * randomFloat() - 0.25f);
	p->velY = 2.0f + (0.5f * randomFloat() - 0.25f);
	p->velZ = 0;//2 * sin(angle) + (0.5f * randomFloat() - 0.25f);
	
	calculate_colour(&(p->colX), &(p->colY), &(p->colZ));
	p->time_alive = 0;
	p->lifespan = randomFloat() + 1;
}

//Advances the particle fountain by STEP_TIME seconds.
void step() 
{
	colorTime += STEP_TIME / 10;
	while (colorTime >= 1) {
		colorTime -= 1;
	}
	
	angle = 150.0f * STEP_TIME;
	while (angle > 2 * PI) {
		angle -= 2 * PI;
	}
	
	for(int i = 0; i < NUM_PARTICLES; i++) {
		Particle* p = particles + i;
		
		p->posX += p->velX * 20 * STEP_TIME;	// spreading the particle effect 
		p->posY += p->velY * 20 * STEP_TIME;	// increasing the velocity makes particle fall faster.
		p->posZ += p->velZ * STEP_TIME;
		
		// calculating the velocity of the paricle
		p->velX += 0.0f;
		p->velY += -GRAVITY * STEP_TIME;
		p->velZ += 0.0f;
		
		p->time_alive += STEP_TIME;
		if (p->time_alive > p->lifespan) {
			create_particle(p);
		}
	}
}

/* creating all the particles in the system*/
void initialise_particle_system_engine()
{
	timeUntilNextStep = 0;
	colorTime = 0;
	angle = 0;
	int i = 0;
	for(i = 0; i < NUM_PARTICLES; i++)
	{
		create_particle(particles + i);
	}
	for(i = 0; i < 5/STEP_TIME; i++)
	{
		step();		// starts stepping through the particle
	}
}

// loading the texture for the particle system
void initialise_particle_system(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	texture = texture_load("white.jpg");
	
	if(!texture)
		printf("\n texture not loaded");
}

// mathematical calculation of normalising a single vector
void normalise(float* x, float* y, float* z)
{
	float m = sqrt((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
	*x = (*x) / m; 
	*y = (*y) / m;
	*z = (*z) / m;
	
}

// cross product of a vector.
void cross(float* crossX, float* crossY, float* crossZ, 
		   float x1, float y1, float z1,
		   float x2, float y2, float z2)
{
	*crossX = y1*z2 - z1*y2;
	*crossY = z1*x2 - x1*z2;
	*crossZ = x1*y2 - y1*x2;
}

// dot product of a vector
float dot(float x1, float y1, float z1,float x2, float y2, float z2)
{
	return x1*x2 + y1*y2 + z1*z2;
}

// finds out the position of the adjacent particle
void adj_particle_pos(float* x, float* y, float* z)
{
	
	//Rotates the vector by the indicated number of degrees about the specified axis
	float axisX = 1; float axisY = 0; float axisZ = 0;
	normalise(&axisX, &axisY, &axisZ);
	float degree = 0;
	float radians = degree * PI /180;
	float s = sin(radians);
	float c = cos(radians);
	float dot_value = dot(*x, *y, *z, axisX, axisY, axisZ);
	
	float crossX = 0; float crossY = 0; float crossZ = 0;
	cross(&crossX, &crossY, &crossZ,
		  *x, *y, *z, axisX, axisY, axisZ);
	
	*x = (*x) * c + axisX * dot_value * (1-c) + crossX * s;
	*y = (*y) * c + axisY * dot_value * (1-c) + crossY * s;
	*z = (*z) * c + axisZ * dot_value * (1-c) + crossZ * s;
}

//Draws the particle fountain.
void draw_particle_system() 
{
	/*vector<Particle*> ps;
	 for(int i = 0; i < NUM_PARTICLES; i++) {
	 ps.push_back(particles + i);
	 }
	 sort(ps.begin(), ps.end(), compareParticles);
	 */
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// drawsthe particle with texture co-orinates
	glBegin(GL_QUADS);
	for(unsigned int i = 0; i < NUM_PARTICLES; i++) {
		Particle* p = particles + i;
		glColor4f(p->colX, p->colY, p->colZ,
				  (1 - p->time_alive / p->lifespan));
		float size = PARTICLE_SIZE / 2;
		
		adj_particle_pos(&(p->posX), &(p->posY), &(p->posZ));
		
		glTexCoord2f(0, 0);
		glVertex3f(p->posX - size, p->posY - size, p->posZ);
		glTexCoord2f(0, 1);
		glVertex3f(p->posX - size, p->posY + size, p->posZ);
		glTexCoord2f(1, 1);
		glVertex3f(p->posX + size, p->posY + size, p->posZ);
		glTexCoord2f(1, 0);
		glVertex3f(p->posX + size, p->posY - size, p->posZ);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);  // changing colour back to white.
}

/* draws the scene depending on the position of the first 
 * or second player camera */
void draw_particle_system_scene(float x, float y, float z, int player1, float rotate_x, float rotate_y)
{
	if (player1) {
		glTranslatef(x-1.0f, 2.0f, z+2.2f);	
	}
	else {
		glTranslatef(x-1.0f, 2.0f, z-2.2f);
	}
	
	glRotatef (rotate_x, 0, -1, 0);
	glRotatef (rotate_y, -1, 0, 0);

	glScalef(.5f, .5f, .5f);
	
	draw_particle_system();
}

//Advances the particle fountain by the specified amount of time.
void advance_particles(float dt) {
	while (dt > 0) {
		if (timeUntilNextStep < dt) {
			dt -= timeUntilNextStep;
			step();
			timeUntilNextStep = STEP_TIME;
		}
		else {
			timeUntilNextStep -= dt;
			dt = 0;
		}
	}
}
