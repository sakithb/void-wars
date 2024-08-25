#ifndef PLAYER_H
#define PLAYER_H

#include "gameobject.h"
#include "raylib.h"

#define PLAYER_HEALTH 100.0f

typedef struct {
	GameObject gameobject;
	int health;
} Player;

void player_init(Player *player);
void player_update(Player *player, Vector2 mouse);
void player_draw(Player *player);
void player_die(Player *player);
void player_free(Player *player);

#endif
