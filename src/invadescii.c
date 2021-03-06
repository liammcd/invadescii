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

#include <curses.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "draw.h"
#include "entities.h"
#include "util.h"

pthread_mutex_t lock;

#define LOCK pthread_mutex_lock(&lock);
#define UNLOCK pthread_mutex_unlock(&lock);
#define TIMESTEP 0.15

typedef struct Args {

	WINDOW *mainwin;
	int *buf;
} Args;

/* Blocking thread to handle user input */
void *keyListener(void *_args) {

	int key;
	int *buf = ((Args *)_args)->buf;
	WINDOW *win = ((Args *)_args)->mainwin;
	keypad(stdscr, TRUE);
		
	while(1) {
		key = wgetch(stdscr);
		LOCK;
		*buf = key;
		UNLOCK;
	}
	return NULL;
}

void initGame(GameInfo *game) {

	game->player = initPlayer(game->x, game->y);
	game->invaders = initInvaders(game->x);
}

void gameLoop(GameInfo *game) {

		int _input;
		int quit = 0;
		clock_t begin, end;
		Args *_args = (Args *) malloc(sizeof(Args));

		/* Thread setup */
		pthread_t keyInput;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		_args->mainwin = game->healthwin;
		_args->buf = &_input;
		
		pthread_create(&keyInput, &attr, keyListener, (void *)_args);

		initGame(game);
	
		while (quit == 0) {
	
			begin = clock();
			/* Get user input and update player position */
			LOCK;
			switch (_input) {
			
				case KEY_LEFT:
					if (game->player->pos.x - 1 > 0)
						game->player->pos.x = game->player->pos.x - 1;
					break;
				case KEY_RIGHT:
					if (game->player->pos.x + 1 < game->x - 1)
						game->player->pos.x = game->player->pos.x + 1;
					break;
				case ' ':
					addMissile(&(game->missiles), game->player->pos, 0);
					break;
				case 'q':
					quit = 1;
					break;
			}
			_input = 0; 
			UNLOCK;
			
			/* Update locations, check collisions */
			fireRandom(game->missiles, game->invaders);
			updateMissiles(game);
			updateInvaders(game);
			
			/* Redraw */
			werase(game->mainwin);
			drawPlayer(game->mainwin, game->player);
			drawHealth(game->healthwin, game->player);
			drawInvaders(game->mainwin, game->invaders);
			drawMissiles(game->mainwin, game->missiles);
			wrefresh(game->mainwin);
			
			end = clock();
			double elap = ((double) end - begin)/CLOCKS_PER_SEC;
			while (elap < TIMESTEP) {
				end = clock();
				elap = ((double) end - begin)/CLOCKS_PER_SEC;
			}
		}

		pthread_cancel(keyInput);
		free(game->player);
		freeMissiles(game->missiles);
		free(_args);		
}

int main(int argc, char *argv[]) {

	GameInfo game;
	
	/* Ncurses setup */
	initscr();
	start_color();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, game.y, game.x);
	game.mainwin = newwin((game.y)-1, game.x, 0, 0);
	game.healthwin = newwin(1, game.x, (game.y)-1, 0);
	init_color(COLOR_GREEN, 0, 1000, 0);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	wbkgd(game.mainwin, COLOR_PAIR(1));
	wbkgd(game.healthwin, COLOR_PAIR(1));
	refresh();

	pthread_mutex_init(&lock, NULL);

	gameLoop(&game);
	
	endwin();
			
	return 0;
}