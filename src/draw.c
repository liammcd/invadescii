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

#include "draw.h"

void drawPlayer(WINDOW *win, Player *player) {

	int x, y;
	x = player->pos.x;
	y = player->pos.y;
	wmove(win, y, x);
	waddch(win, ACS_CKBOARD);
	wmove(win, y-1, x);
	waddch(win, ACS_CKBOARD);
	wmove(win, y, x-1);
	waddch(win, ACS_CKBOARD);
	wmove(win, y, x+1);
	waddch(win, ACS_CKBOARD);
}

void drawInvaders(WINDOW *win, Invader *invaders) {

	Invader *i = invaders;
	int x, y;
	while (i != NULL) {
		x = i->pos.x;
		y = i->pos.y;
		wmove(win, y, x);
		waddch(win, 'x');
		i = i->next;
	}
}

void drawMissiles(WINDOW *win, Missile *missiles) {
	
	Missile *m = missiles;
	int x, y;
	while (m != NULL) {
		x = m->pos.x;
		y = m->pos.y;
		wmove(win, y, x);
		waddch(win, 'o');
		m = m->next;
	}
}

void drawHealth(WINDOW *win, Player *player) {

	werase(win);
	wprintw(win, "HEALTH: %d", player->health);
	wrefresh(win);
}