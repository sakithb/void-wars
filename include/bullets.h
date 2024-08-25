#ifndef BULLETS_H
#define BULLETS_H

#include <stdbool.h>
#include "raylib.h"
#include "gameobject.h"
#include "enemies.h"

#define MAX_BULLETS 10
#define MAX_BULLET_DISTANCE 500
#define BULLET_DAMAGE 10.0f

typedef struct {
	GameObject gameobject;
	Vector2 target;
	Vector2 source;
	bool usable;
} Bullet;

void bullet_init(Bullet *bullet, Vector2 target, Vector2 source);
void bullet_update(Bullet *bullet);
void bullet_die(Bullet *bullet);

typedef struct {
	int count;
	Bullet bullets[MAX_BULLETS];
} BulletStack;

void bulletstack_init(BulletStack *bullet_stack);
void bulletstack_shoot(BulletStack *bullet_stack, Vector2 target, Vector2 source);
void bulletstack_draw(BulletStack *bullet_stack);
void bulletstack_update(BulletStack *bullet_stack, EnemyManager *enemy_manager);
void bulletstack_free(BulletStack *bullet_stack);

#endif
