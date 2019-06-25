#ifndef _DRAW_H
#define _DRAW_H

#include <curses.h>

#include "entities.h"

void drawPlayer(WINDOW *win, Player *player);
void drawInvaders(WINDOW *win, Invader *invaders);
void drawMissiles(WINDOW *win, Missile *missiles);

#endif