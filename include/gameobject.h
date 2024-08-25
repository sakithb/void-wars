#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdbool.h>
#include "raylib.h"

#define DEFAULT_ANIM_SPEED 100
#define DEFAULT_SPEED 100

typedef struct {
	Texture2D texture;

	Vector2 position;
	Vector2 origin;
	Vector2 velocity;

	float rotation;
	float speed;
	float anim_start;
	float anim_speed;
	bool frame_freezed;

	int frame_size;
	int frame_count;
	int frame;
} GameObject;

void gameobject_init(GameObject *gameobject, const char *texture_path, int frame_size, int frame_count);
void gameobject_lookat(GameObject *gameobject, Vector2 target);
void gameobject_update(GameObject *gameobject);
void gameobject_draw(GameObject *gameobject);
void gameobject_free(GameObject *gameobject);

#endif
