#ifndef _ENTITIES_H
#define _ENTITIES_H

#include <curses.h>

typedef struct Position {
	
	int x, y;
} Position; 

typedef struct Player {

	Position pos;
	int health;
} Player;

// Store missiles in a linked list 
typedef struct Missile {
	
	Position pos;
	int direction; // 0 -> up ; 1 -> down
	struct Missile *next;
} Missile;

// Store invaders in a linked list
typedef struct Invader {

	Position pos;
	int direction; // 0 -> left ; 1 -> right
	struct Invader *next;
} Invader;

typedef struct GameInfo {

	Player *player;
	Invader *invaders;
	Missile *missiles;
	WINDOW *mainwin;
	WINDOW *scorewin;
	int x, y; // Screen size
} GameInfo;

Player *initPlayer(int x, int y);
Invader *initInvaders(int x);
Missile *initMissiles();
void addMissile(Missile **missiles, Position pos, int dir);
void updateMissiles(GameInfo *game);
void freeMissiles(Missile *missiles);

#endif