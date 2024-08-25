#include "../include/player.h"
#include "../include/screens.h"
#include "../include/contants.h"
#include "../include/utils.h"

void player_init(Player *player) {
	gameobject_init(&player->gameobject, "assets/player.png", 32, 5);
	player->gameobject.position.x = RWIDTH / 2.0f;
	player->gameobject.position.y = RHEIGHT / 2.0f;
	player->health = PLAYER_HEALTH;
}

void player_update(Player *player, Vector2 mouse) {
	gameobject_lookat(&player->gameobject, mouse);
	gameobject_update(&player->gameobject);

	player->gameobject.position.x = MIN(MAX(0, player->gameobject.position.x), RWIDTH);
	player->gameobject.position.y = MIN(MAX(0, player->gameobject.position.y), RHEIGHT);

	if (player->gameobject.velocity.x == 0 && player->gameobject.velocity.y == 0) {
		player->gameobject.frame_freezed = true;
		player->gameobject.frame = 4;
	} else {
		player->gameobject.frame_freezed = false;
	}

	if (player->health <= 0) {
		player_die(player);
	}

	if (state.score >= 20) {
		player->gameobject.speed = DEFAULT_SPEED * 1.5;
	} else if (state.score >= 50) {
		player->gameobject.speed = DEFAULT_SPEED * 2;
	} else if (state.score >= 100) {
		player->gameobject.speed = DEFAULT_SPEED * 3;
	} else if (state.score >= 150) {
		player->gameobject.speed = DEFAULT_SPEED * 4;
	} else if (state.score >= 200) {
		player->gameobject.speed = DEFAULT_SPEED * 5;
	} else {
		player->gameobject.speed = DEFAULT_SPEED * 1.25;
	}
}

void player_draw(Player *player) {
	gameobject_draw(&player->gameobject);
	healthbar_draw(player->gameobject.position, (float)player->health / PLAYER_HEALTH);
}

void player_die(Player *player) {
	state.screen = ENDING;
}

void player_free(Player *player) {
	gameobject_free(&player->gameobject);
}
