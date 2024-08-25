#include "../include/enemies.h"
#include "../include/screens.h"
#include "../include/contants.h"
#include "../include/utils.h"
#include "raymath.h"

void enemy_init(Enemy *enemy) {
	int blocks = MAX_ENEMIES/4;
	int x_spacing = RWIDTH / blocks;
	int y_spacing = RHEIGHT / blocks;

	GameObject *gameobject = (GameObject*)enemy;

	int s = GetRandomValue(0, 4);
	int i = GetRandomValue(0, blocks);

	if (s == 0) {
		gameobject->position.x = x_spacing * i;
		gameobject->position.y = -64;
	} else if (s == 1) {
		gameobject->position.x = RWIDTH + 64;
		gameobject->position.y = y_spacing * i;
	} else if (s == 2) {
		gameobject->position.x = x_spacing * i;
		gameobject->position.y = RHEIGHT + 64;
	} else if (s == 3) {
		gameobject->position.x = -64;
		gameobject->position.y = y_spacing * i;
	}

	enemy->target = gameobject->position;
	enemy->health = ENEMY_HEALTH;
}

void enemy_update(Enemy *enemy, GameObject *player) {
	GameObject *gameobject = (GameObject*)enemy;

	float distance = Vector2Distance(gameobject->position, player->position);
	if (distance < ENEMY_SIGHT) {
		gameobject_lookat(gameobject, player->position);
		gameobject->speed = DEFAULT_SPEED;
	} else {
		if (Vector2Distance(gameobject->position, enemy->target) <= 20.0f) {
			int roam_distance_x = RWIDTH / 4;
			int roam_distance_y = RHEIGHT / 4;

			float x = GetRandomValue(-roam_distance_x, roam_distance_x);
			float y = GetRandomValue(-roam_distance_y, roam_distance_y);

			if (gameobject->position.x <= 100) {
				x *= -1;
			} else if (gameobject->position.x >= RWIDTH - 100 && x > 0) {
				x *= -1;
			}

			if (gameobject->position.y <= 100 && y < 0) {
				y *= -1;
			} else if (gameobject->position.y >= RHEIGHT - 100 && y > 0) {
				y *= -1;
			}

			enemy->target = Vector2Add(gameobject->position, (Vector2){x, y});

			enemy->target.x = MIN(MAX(32, enemy->target.x), RWIDTH - 32);
			enemy->target.y = MIN(MAX(32, enemy->target.y), RHEIGHT - 32);

			gameobject_lookat(gameobject, enemy->target);
		}

		gameobject->speed = DEFAULT_SPEED * 0.5;
	}

	gameobject_update(gameobject);

	if (enemy->health <= 0) {
		enemy_die(enemy);
	}
}

void enemy_die(Enemy *enemy) {
	explosionmanager_explode(&state.explosion_manager, enemy->gameobject.position);

	if (enemy->health <= 0) {
		state.score++;
	}

	enemy_init(enemy);
}

void enemymanager_init(EnemyManager *enemy_manager, Player *player) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		Enemy *enemy = &enemy_manager->enemies[i];
		GameObject *gameobject = (GameObject*)enemy;
		gameobject_init(gameobject, "assets/enemy.png", 32, 6);
		enemy_init(enemy);

		enemy->gameobject.velocity.y = -1;
	}

	enemy_manager->player = player;
}

void enemymanager_update(EnemyManager *enemy_manager) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		Enemy *enemy = &enemy_manager->enemies[i];
		Rectangle rec_enemy = (Rectangle){enemy->gameobject.position.x, enemy->gameobject.position.y, enemy->gameobject.frame_size, enemy->gameobject.frame_size};
		Rectangle rec_player = (Rectangle){enemy_manager->player->gameobject.position.x, enemy_manager->player->gameobject.position.y, enemy_manager->player->gameobject.frame_size, enemy_manager->player->gameobject.frame_size};

		if (CheckCollisionRecs(rec_enemy, rec_player)) {
			enemy_manager->player->health -= ENEMY_DAMAGE;
			enemy_die(enemy);
		} else {
			enemy_update(enemy, &enemy_manager->player->gameobject);
		}
	}
}

void enemymanager_draw(EnemyManager *enemy_manager) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		Enemy *enemy = &enemy_manager->enemies[i];
		GameObject *gameobject = (GameObject*)enemy;

		gameobject_draw(gameobject);
		healthbar_draw(gameobject->position, (float)enemy->health / ENEMY_HEALTH);
	}
}

void enemymanager_free(EnemyManager *enemy_manager) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		GameObject *gameobject = (GameObject*)&enemy_manager->enemies[i];
		gameobject_free(gameobject);
	}
}
