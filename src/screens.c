#include "../include/screens.h"
#include "../include/contants.h"
#include <raylib.h>

void state_init() {
	player_init(&state.player);
	bulletstack_init(&state.bullet_stack);
	enemymanager_init(&state.enemy_manager, &state.player);
	explosionmanager_init(&state.explosion_manager);

	state.camera.target = state.player.gameobject.position;
	state.camera.zoom = 1.5f;
	state.camera.offset = (Vector2){RWIDTH/2.0f, RHEIGHT/2.0f};
	state.camera.rotation = 0;

	state.score = 0.0f;
	state.screen = TITLE;
}

void gamescreen_update_title() {
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		state.screen = GAMEPLAY;
	}
}

void gamescreen_update_gameplay() {
	// Updates

	if (IsKeyDown(KEY_W)) {
		state.player.gameobject.velocity.y = -1;
	} else {
		state.player.gameobject.velocity.y = 0;
	}

	if (IsKeyDown(KEY_D)) {
		state.player.gameobject.velocity.x = 1;
	} else if (IsKeyDown(KEY_A)) {
		state.player.gameobject.velocity.x = -1;
	} else {
		state.player.gameobject.velocity.x = 0;
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		bulletstack_shoot(&state.bullet_stack, state.mouse_pos, state.player.gameobject.position);
	}

	// Fixed updates

	player_update(&state.player);
	enemymanager_update(&state.enemy_manager);
	explosionmanager_update(&state.explosion_manager);
	bulletstack_update(&state.bullet_stack, &state.enemy_manager);

	state.camera.target.x += (state.player.gameobject.position.x - state.camera.target.x) * GetFrameTime() * 2.0f;
	state.camera.target.y += (state.player.gameobject.position.y - state.camera.target.y) * GetFrameTime() * 2.0f;

	state.camera.target.x = MIN(MAX(state.camera.offset.x / state.camera.zoom, state.camera.target.x), RWIDTH - (state.camera.offset.x / state.camera.zoom));
	state.camera.target.y = MIN(MAX(state.camera.offset.y / state.camera.zoom, state.camera.target.y), RHEIGHT - (state.camera.offset.y / state.camera.zoom));
}

void gamescreen_update_ending() {
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		state_init();
		state.screen = GAMEPLAY;
	}
}

void gamescreen_draw_title() {
	int width = MeasureText("Click to play", 32);
	DrawText("Click to play", RWIDTH / 2 - width / 2, RHEIGHT / 2 - 16, 32, WHITE);
}

void gamescreen_draw_gameplay() {
	BeginMode2D(state.camera);
		player_draw(&state.player);
		enemymanager_draw(&state.enemy_manager);
		explosionmanager_draw(&state.explosion_manager);
		bulletstack_draw(&state.bullet_stack);
	EndMode2D();

	const char *score_text = TextFormat("%d", state.score);
	int score_width = MeasureText(score_text, 32);

	DrawText(score_text, 16, 16, 32, WHITE);
}

void gamescreen_draw_ending() {
	const char *score_text = TextFormat("Score: %d", state.score);

	int gameover_width = MeasureText("Gameover", 64);
	int score_width = MeasureText(score_text, 32);
	int replay_width = MeasureText("Click to replay", 32);

	Vector2 gameover_pos = (Vector2){RWIDTH / 2.0f - gameover_width / 2.0f, RHEIGHT / 2.0f - 64};
	Vector2 score_pos = (Vector2){RWIDTH / 2.0f - score_width / 2.0f, RHEIGHT / 2.0f};
	Vector2 replay_pos = (Vector2){RWIDTH / 2.0f - replay_width / 2.0f, RHEIGHT / 2.0f + 64};

	DrawText("Gameover", gameover_pos.x, gameover_pos.y, 64, WHITE);
	DrawText(score_text, score_pos.x, score_pos.y, 32, WHITE);
	DrawText("Click to replay", replay_pos.x, replay_pos.y, 32, WHITE);
}
