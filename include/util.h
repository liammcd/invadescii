#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>

int countInvaders(Invader *invaders);
int randNum(int max);

/* Invaders randomly fire */
void fireRandom(Missile *missiles, Invader *invaders);

#endif