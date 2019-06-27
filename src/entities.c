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

	Invader *invaders;
	Invader *head;
	
	// Determine number of invaders to create (from x values?
	
	int val = floor(x/4);
	int i;
	
	invaders = (Invader *) malloc(sizeof(Invader));
	invaders->next = NULL;
	invaders->pos.y = 0;
	invaders->pos.x = 1;
	invaders->direction = 1; // Start rightward
	head = invaders;
	
	for (i = 1; i <= val; i++) {
		invaders->next = (Invader *) malloc(sizeof(Invader));
		invaders = invaders->next;
		invaders->next = NULL;
		invaders->pos.y = 0;
		invaders->pos.x = 1 + i*2;
		invaders->direction = 1;
	} 
	
	return head;
}

void addMissile(Missile **missiles, Position pos, int dir) {

	Missile *m = *missiles;
	
	if (m == NULL) {
		*missiles = (Missile *) malloc(sizeof(Missile));
		m = *missiles;
		m->pos.x = pos.x;
		m->pos.y = pos.y - 1;
		m->direction = dir;
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
		m->direction = dir;
	}
}

/* Advance missiles and check for collisions */
void updateMissiles(GameInfo *game) {
	
	Missile *m = game->missiles;
	Missile *prev;
	Invader *invader;
	Invader *prevInvader;
	int px = game->player->pos.x;
	int py = game->player->pos.y;
	while (m != NULL) {
		if (m->direction == 0) { // Up direction
			if (m->pos.y - 1 < 0) { // Gone off screen, remove
				if (m == game->missiles) { // Missile is at head of ll
					game->missiles = m->next;
					free(m);
				}
				else {
					prev->next = m->next;
					free(m);
				}
			}
			else { // Move up
				m->pos.y = m->pos.y - 1;
				// Check for collision with invaders
				invader = game->invaders;
				prevInvader = invader;
				while (invader != NULL) {
					if (invader->pos.x == m->pos.x && invader->pos.y == m->pos.y) {
						// Collision; remove invader and missile
						if (invader == game->invaders) {
							game->invaders = invader->next;
							free(invader);
						}
						else {
							prevInvader->next = invader->next;
							free(invader);
						}
					}
					prevInvader = invader;
					invader = invader->next;
				}
			}
		}
		else if (m->direction == 1) {// Down direction
			if (m->pos.y + 1 > (game->y-2)) { // Gone off screen, remove
				if (m == game->missiles) {
					game->missiles = m->next;
					free(m);
				}
				else {
					prev->next = m->next;
					free(m);
				}
			}
			else { // Move down
				m->pos.y = m->pos.y + 1;
				// Check for collision with player
				if (m->pos.x == px && m->pos.y == py) {
					game->player->health = game->player->health - 5;
					if (m == game->missiles) {
						game->missiles = m->next;
						free(m);
					}
					else {
						prev->next = m->next;
						free(m);
					}
				}	
				else if (m->pos.x == (px-1) && m->pos.y == py) {
					game->player->health = game->player->health - 5;
					if (m == game->missiles) {
						game->missiles = m->next;
						free(m);
					}
					else {
						prev->next = m->next;
						free(m);
					}
				}
				else if (m->pos.x == (px+1) && m->pos.y == py) {
					game->player->health = game->player->health - 5;
					if (m == game->missiles) {
						game->missiles = m->next;
						free(m);
					}
					else {
						prev->next = m->next;
						free(m);
					}
				}	
			}
		}
		prev = m;
		m = m->next;
	}
}

void updateInvaders(GameInfo *game) {

	Invader *i = game->invaders;
	Invader *last;
	if (i == NULL)
		return;
	switch (i->direction) {
		case LEFT:
			if (i->pos.x - 2 < 0) { // Hit left wall
				while (i != NULL) {
					i->direction = 1;
					i->pos.y = i->pos.y + 1;
					i = i->next;
				}
			}
			else { // Advance
				while (i != NULL) {
					i->pos.x = i->pos.x - 2;
					i = i->next;
				}
			}
			break;
		case RIGHT:
			while (i != NULL) {
				last = i;
				i = i->next;	
			}
			if (last->pos.x + 2 > game->x - 1) { // Hit right wall
				i = game->invaders;
				while (i != NULL) {
					i->direction = 0; // Switch direction
					i->pos.y = i->pos.y + 1;
					i = i->next;
				}
			}
			else { // Advance
				i = game->invaders;
				while (i != NULL) {
					i->pos.x = i->pos.x + 2;
					i = i->next;
				}
			}
			break;
	}
}

void freeMissiles(Missile *missiles) {

	Missile *m = missiles;
	Missile *next;
	while (m != NULL) {
		next = m->next;
		free(m);
		m = next;
	}
}