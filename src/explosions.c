#include "../include/explosions.h"

void explosionmanager_init(ExplosionManager *explosion_manager) {
	for (int i = 0; i < EXPLOSION_INSTANCES; i++) {
		GameObject *gameobject = &explosion_manager->explosions[i];
		gameobject_init(gameobject, "assets/explosion.png", 32, 6);
		gameobject->frame_freezed = true;
		gameobject->anim_speed = DEFAULT_ANIM_SPEED / 1.5;
	}
}

void explosionmanager_update(ExplosionManager *explosion_manager) {
	for (int i = 0; i < EXPLOSION_INSTANCES; i++) {
		GameObject *gameobject = &explosion_manager->explosions[i];
		if (gameobject->frame_freezed) continue;

		if (gameobject->frame == gameobject->frame_count-1) {
			gameobject->frame_freezed = true;
		}
	}
}

void explosionmanager_explode(ExplosionManager *explosion_manager, Vector2 position) {
	for (int i = 0; i < EXPLOSION_INSTANCES; i++) {
		GameObject *gameobject = &explosion_manager->explosions[i];
		if (gameobject->frame_freezed) {
			gameobject->position = position;
			gameobject->frame_freezed = false;
			gameobject->frame = 0;
			break;
		}
	}
}

void explosionmanager_draw(ExplosionManager *explosion_manager) {
	for (int i = 0; i < EXPLOSION_INSTANCES; i++) {
		GameObject *gameobject = &explosion_manager->explosions[i];
		if (!gameobject->frame_freezed) {
			gameobject_draw(gameobject);
		}
	}
}

void explosionmanager_free(ExplosionManager *explosion_manager) {
	for (int i = 0; i < EXPLOSION_INSTANCES; i++) {
		GameObject *gameobject = &explosion_manager->explosions[i];
		gameobject_free(gameobject);
	}
}
