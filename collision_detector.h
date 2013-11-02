#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include "gl.h"
#include "utility.h"
#include "cannon.h"
#define SHIP_RADIUS 0.35f

extern int player_1_lives;
extern int player_2_lives;

int shipsCollided(GLOBAL_Translate*, GLOBAL_Translate*);
void initPlayers();
int shipDamaged(int, GLOBAL_Translate*, GLOBAL_CANNON_SHOT*);
int cannonHitShip(GLOBAL_Translate, GLOBAL_Translate);
double calculate_distance(GLOBAL_Translate, GLOBAL_Translate);

#endif