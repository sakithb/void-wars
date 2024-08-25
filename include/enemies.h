#ifndef ENEMIES_H
#define ENEMIES_H

#include <stdbool.h>
#include "gameobject.h"
#include "player.h"

#define MAX_ENEMIES 40
#define ENEMY_HEALTH 20.0f
#define ENEMY_DAMAGE 5.0f
#define ENEMY_SIGHT 400.0f

typedef struct {
	GameObject gameobject;
	Vector2 target;
	int health;
} Enemy;

void enemy_init(Enemy *enemy);
void enemy_update(Enemy *enemy, GameObject *player);
void enemy_die(Enemy *enemy);

typedef struct {
	Enemy enemies[MAX_ENEMIES];
	Player *player;
} EnemyManager;

void enemymanager_init(EnemyManager *enemy_manager, Player *player);
void enemymanager_draw(EnemyManager *enemy_manager);
void enemymanager_update(EnemyManager *enemy_manager);
void enemymanager_free(EnemyManager *enemy_manager);

#endif
