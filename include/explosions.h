#ifndef EXPLOSIONS_H
#define EXPLOSIONS_H

#include "raylib.h"
#include "gameobject.h"
#include "enemies.h"

#define EXPLOSION_INSTANCES MAX_ENEMIES + 1

typedef struct {
	GameObject explosions[EXPLOSION_INSTANCES];
} ExplosionManager;

void explosionmanager_init(ExplosionManager *explosion_manager);
void explosionmanager_update(ExplosionManager *explosion_manager);
void explosionmanager_explode(ExplosionManager *explosion_manager, Vector2 position);
void explosionmanager_draw(ExplosionManager *explosion_manager);
void explosionmanager_free(ExplosionManager *explosion_manager);

#endif
