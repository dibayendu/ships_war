#include "collision_detector.h"

int player_1_lives;
int player_2_lives;

/* initialising players with their default lives. */
void initPlayers()
{
	player_1_lives = 3;	
	player_2_lives = 3;
}

/* checks if both the ships collided with each other. Return TRUE if so. */
int shipsCollided(GLOBAL_Translate* translateShip_1, GLOBAL_Translate* translateShip_2) 
{
	double ships_distance = calculate_distance(*translateShip_1, *translateShip_2);
	double radius_of_two_ships = (SHIP_RADIUS) * 2; // since there are two ships of same size. 

	if (ships_distance <= radius_of_two_ships) {
		return TRUE;
	}
	
	return FALSE;
}

/* checks and returns palyers lives left when a cannon has hit a ship. */
int shipDamaged(int player_life, GLOBAL_Translate* translateShip, GLOBAL_CANNON_SHOT* cannon_shots)
{
	int lives_left = player_life;
	int i = 0;
	
	// goes through all the cannon shots which have been fired. 
	for ( i = 0; i < TOTAL_CANNON_SHOTS; i++) {
		if (cannon_shots[i].fired && !cannon_shots[i].drowned)
		{
			int hit = cannonHitShip(*translateShip, cannon_shots[i].translateShot);
			if (hit) 
			{
				cannon_shots[i].drowned = SHOT_DROWNED;
				lives_left --;
			}
		}
	}
	return lives_left;
}

/* check if a particular shot hit the ship. */
int cannonHitShip(GLOBAL_Translate translateShip, GLOBAL_Translate translateShot)
{
	double ship_shot_distance = calculate_distance(translateShip, translateShot);
	double radius_of_ship_and_shot = SHIP_RADIUS + SHOT_RADIUS;
	if (ship_shot_distance < radius_of_ship_and_shot) {
		return TRUE;
	}
	
	return FALSE;
}

/* using vector formaula caluculates distance between two objects. */
double calculate_distance(GLOBAL_Translate object_1, GLOBAL_Translate object_2)
{
	return sqrt(
						( (object_1.posX - object_2.posX) * (object_1.posX - object_2.posX))
					+	( (object_1.posY - object_2.posY) * (object_1.posY - object_2.posY))
					+	( (object_1.posZ - object_2.posZ) * (object_1.posZ - object_2.posZ))
				);
}