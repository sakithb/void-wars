#ifndef SCREENS_H
#define SCREENS_H

#include "bullets.h"
#include "explosions.h"
#include "player.h"

typedef enum {
	TITLE = 0,
	GAMEPLAY,
	ENDING
} GameScreen;

typedef struct {
	int score;

	GameScreen screen;
	Player player;
	BulletStack bullet_stack;
	EnemyManager enemy_manager;
	ExplosionManager explosion_manager;
	Camera2D camera;
} State;

void state_init();

void gamescreen_update_title(); 
void gamescreen_update_gameplay(); 
void gamescreen_update_ending(); 

void gamescreen_draw_title(); 
void gamescreen_draw_gameplay(); 
void gamescreen_draw_ending(); 

extern State state;

#endif
