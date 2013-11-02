#ifndef KEYS_H
#define KEYS_H

#include "gl.h"
#include "axes.h"
#include "waves.h"
#include "ship.h"
#include "cannon.h"
#include "utility.h"

void initAllKeys(void);
void shipMovementKeys(GLOBAL_MovementKeys*, int, int);
void keyboardKeys(unsigned char);
void secondShipKeys(unsigned char,int);

#endif