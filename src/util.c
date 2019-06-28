#include "entities.h"
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

#include "util.h"

/* Return random number between 0 and limit inclusive */
int randNum(int max) {

	int divisor = RAND_MAX/(max+1);
	int retval;
	
	do {
		retval = rand() / divisor;
	} while (retval > max);
	
	return retval;
}

int countInvaders(Invader *invaders) {

	int count = 0;
	Invader *i = invaders;
	while (i != NULL) {
		count += 1;
		i = i->next;
	}
	return count;
}

void fireRandom(Missile *missiles, Invader *invaders) {
	
	int numInvaders, i, shooterNum;
	Invader *shooter;
	Position pos;
	
	if (randNum(5) == 0) {
		// Choose random invader to fire
		numInvaders = countInvaders(invaders);
		shooterNum = randNum(numInvaders);
		shooter = invaders;
		for (i = 1; i < shooterNum; i++) {
			shooter = shooter->next;
		}
		if (shooter != NULL) {
			pos.x = shooter->pos.x;
			pos.y = shooter->pos.y + 1;
			addMissile(&(missiles), pos, 1);
		}
	}
}