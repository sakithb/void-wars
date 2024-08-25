#include "../include/bullets.h"
#include "raymath.h"

void bullet_init(Bullet *bullet, Vector2 target, Vector2 source) {
	bullet->usable = false;
	bullet->target = target;
	bullet->source = source;

	GameObject *gameobject = (GameObject*)bullet;

	gameobject->position = source;
	gameobject->velocity = Vector2Normalize(Vector2Subtract(target, source));

	gameobject->frame = 0;
	gameobject->frame_freezed = true;
}

void bullet_update(Bullet *bullet) {
	GameObject *gameobject = (GameObject*)bullet;
	gameobject_update(gameobject);

	float distance = Vector2Distance(gameobject->position, bullet->source);
	if (distance > MAX_BULLET_DISTANCE || !gameobject->frame_freezed) {
		bullet_die(bullet);
	}
}

void bullet_die(Bullet *bullet) {
	GameObject *gameobject = (GameObject*)bullet;

	if (gameobject->frame_freezed) {
		gameobject->frame_freezed = false;

		gameobject->velocity.x =  0;
		gameobject->velocity.y =  0;
	} else if (gameobject->frame == gameobject->frame_count-1) {
		bullet->usable = true;
	}
}

void bulletstack_init(BulletStack *bullet_stack) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		Bullet *bullet = &bullet_stack->bullets[i];
		GameObject *gameobject = (GameObject*)bullet;
		gameobject_init(gameobject, "assets/bullet.png", 8, 9);

		bullet->usable = true;

		gameobject->speed = DEFAULT_SPEED * 5;
		gameobject->anim_speed = DEFAULT_ANIM_SPEED / 2.0;
	}

	bullet_stack->count = 0;
}

void bulletstack_shoot(BulletStack *bullet_stack, Vector2 target, Vector2 source) {
	if (bullet_stack->count == MAX_BULLETS) return;

	for (int i = 0; i < MAX_BULLETS; i++) {
		Bullet *bullet = &bullet_stack->bullets[i];
		if (bullet->usable) {
			bullet_init(bullet, target, source);
			bullet_stack->count++;
			break;
		}
	}
}

void bulletstack_draw(BulletStack *bullet_stack) {
	if (bullet_stack->count == 0) return;

	for (int i = 0; i < MAX_BULLETS; i++) {
		Bullet *bullet = &bullet_stack->bullets[i];
		if (!bullet->usable) {
			GameObject *gameobject = (GameObject*)bullet;
			gameobject_draw(gameobject);
		}
	}
}

void bulletstack_update(BulletStack *bullet_stack, EnemyManager *enemy_manager) {
	if (bullet_stack->count == 0) return;

	for (int i = 0; i < MAX_BULLETS; i++) {
		Bullet *bullet = &bullet_stack->bullets[i];
		if (!bullet->usable) {
			bullet_update(bullet);

			if (bullet->gameobject.frame_freezed) {
				Rectangle rec_bullet = {bullet->gameobject.position.x, bullet->gameobject.position.y, bullet->gameobject.frame_size, bullet->gameobject.frame_size};
				Rectangle rec_enemy = {};
				for (int e = 0; e < MAX_ENEMIES; e++) {
					Enemy *enemy = &enemy_manager->enemies[e];

					rec_enemy.x = enemy->gameobject.position.x;
					rec_enemy.y = enemy->gameobject.position.y;
					rec_enemy.width = enemy->gameobject.frame_size;
					rec_enemy.height = enemy->gameobject.frame_size;

					if (CheckCollisionRecs(rec_bullet, rec_enemy)) {
						enemy->health -= BULLET_DAMAGE;
						bullet_die(bullet);
					}
				}
			}

			if (bullet->usable) {
				bullet_stack->count--;
			}
		}
	}
}

void bulletstack_free(BulletStack *bullet_stack) {
	for (int i = 0; i < MAX_BULLETS; i++) {
		Bullet *bullet = &bullet_stack->bullets[i];
		GameObject *gameobject = (GameObject*)bullet;
		gameobject_free(gameobject);
	}
}
