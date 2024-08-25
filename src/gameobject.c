#include <math.h>
#include "../include/gameobject.h"
#include "raymath.h"

void gameobject_init(
		GameObject *gameobject,
		const char *texture_path,
		int frame_size,
		int frame_count
	) {
	if (gameobject->texture.id <= 0) {
		gameobject->texture = LoadTexture(texture_path);
	}

	gameobject->position = (Vector2){0};
	gameobject->origin = (Vector2){frame_size/2.0, frame_size/2.0};
	gameobject->velocity = (Vector2){0};

	gameobject->rotation = 0;
	gameobject->speed = DEFAULT_SPEED;
	gameobject->anim_speed = DEFAULT_ANIM_SPEED;
	gameobject->anim_start = 0.0f;
	gameobject->frame_freezed = false;

	gameobject->frame_size = frame_size;
	gameobject->frame_count = frame_count;
	gameobject->frame = 0;
}

void gameobject_lookat(GameObject *gameobject, Vector2 target) {
	Vector2 rotation = Vector2Normalize(Vector2Subtract(gameobject->position, target));
	gameobject->rotation = atan2(rotation.y, rotation.x) - (PI/180 * 90);
}

void gameobject_update(GameObject *gameobject) {
	Vector2 rotated_velocity = Vector2Rotate(gameobject->velocity, gameobject->rotation);
	gameobject->position = Vector2Add(gameobject->position, Vector2Scale(rotated_velocity, gameobject->speed * GetFrameTime()));
}

void gameobject_draw(GameObject *gameobject) {
	Rectangle src = {gameobject->frame * gameobject->frame_size, 0, gameobject->frame_size, gameobject->frame_size};
	Rectangle dst = {gameobject->position.x, gameobject->position.y, gameobject->frame_size, gameobject->frame_size};

	DrawTexturePro(
		gameobject->texture,
		src,
		dst,
		gameobject->origin,
		gameobject->rotation * 180/PI,
		WHITE);

	if (gameobject->frame_freezed) {
		gameobject->anim_start = 0.0f;
	} else {
		if (gameobject->anim_start == 0.0f) {
			gameobject->anim_start = GetTime();
		}

		gameobject->frame = (int)((GetTime() - gameobject->anim_start) * 1000 / gameobject->anim_speed) % gameobject->frame_count;
	}
}

void gameobject_free(GameObject *gameobject) {
	UnloadTexture(gameobject->texture);
}
