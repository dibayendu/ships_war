#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "gl.h"
#include "texture_loader_mac.h"
#include "utility.h"

#define GRAVITY 9.8f
#define NUM_PARTICLES 100000
#define STEP_TIME 0.01f
#define PARTICLE_SIZE 0.007f

typedef struct
{
	float posX; float posY; float posZ;
	float velX; float velY; float velZ;
	float colX; float colY; float colZ;
	float time_alive;
	float lifespan;
}Particle;

void advance_particles(float);
void draw_particle_system_scene(float, float, float, int, float, float);
void draw_particle_system();
void adj_particle_pos(float*, float*, float*);
float dot(float, float, float,float, float, float);
void cross(float*, float*, float*, float, float, float,float, float, float);
void normalise(float*, float*, float*);
void initialise_particle_system(void);
void initialise_particle_system_engine();
void step();
void create_particle(Particle*);
void calculate_colour(float*,float*, float*);
float randomFloat();

#endif
