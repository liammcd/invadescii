#ifndef _ENTITIES_H
#define _ENTITIES_H

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

Player *initPlayer(int x, int y);
Invader *initInvaders(int x);
Missile *initMissiles();
void addMissile(Missile **missiles, Position pos);
void updateMissiles(Missile *missiles);

#endif