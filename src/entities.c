/*

Invadescii - a simple ascii invaders-like using ncurses
 
Copyright (C) 2019 Liam McDermott
  
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "entities.h"

Player *initPlayer(int x, int y) {

	Player *player = (Player *) malloc(sizeof(Player));
	player->pos.x = floor(x/2);
	player->pos.y = y-2;
	player->health = 100;
	return player;
}

Invader *initInvaders(int x) {

	Invader *invaders = (Invader *) malloc(sizeof(Invader));
	
	// Determine number of invaders to create (from x values?
	
	return invaders;
}

Missile *initMissiles() {

	//Missile *missiles = (Missile *) malloc(sizeof(Missile));
	//missiles->next = NULL;
	//return missiles;
	return NULL;
}

void addMissile(Missile **missiles, Position pos) {

	Missile *m = *missiles;
	
	if (m == NULL) {
		*missiles = (Missile *) malloc(sizeof(Missile));
		m = *missiles;
		m->pos.x = pos.x;
		m->pos.y = pos.y - 1;
		m->next = NULL;
	}		
	else {
		while (m->next != NULL) {
			m = m->next;
		}
	
		m->next = (Missile *) malloc(sizeof(Missile));
		m = m->next;
		m->next = NULL;
		m->pos.x = pos.x;
		m->pos.y = pos.y - 1;
	}
}

void updateMissiles(Missile *missiles) {
	
	Missile *m = missiles;
	while (m != NULL) {
		m->pos.y = m->pos.y - 1;
		m = m->next;
	}
}