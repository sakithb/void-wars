#include "raylib.h"
#include "../include/contants.h"
#include "../include/screens.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

RenderTexture fbo;
Texture bg;
float bg_scale;
State state = {0};

void game_loop();

int main() {
	InitWindow(1920, 1080, "Void Wars");
	ToggleFullscreen();
	
	fbo = LoadRenderTexture(RWIDTH, RHEIGHT);

	bg = LoadTexture("assets/bg.png");
	bg_scale = MIN((float)RWIDTH/bg.width, (float)RHEIGHT/bg.height);

	state_init();

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(game_loop, 0, 1);
#else
	while(!WindowShouldClose()) {
		game_loop();
	}
#endif


	bulletstack_free(&state.bullet_stack);
	explosionmanager_free(&state.explosion_manager);
	enemymanager_free(&state.enemy_manager);
	player_free(&state.player);

	UnloadTexture(bg);
	UnloadRenderTexture(fbo);

	CloseWindow();
}

void game_loop() {
	float fbo_scale = MIN((float)GetScreenWidth()/RWIDTH, (float)GetScreenHeight()/RHEIGHT);

	switch (state.screen) {
	case TITLE:
		gamescreen_update_title();
		break;
	case GAMEPLAY:
		gamescreen_update_gameplay();
		break;
	case ENDING:
		gamescreen_update_ending();
		break;
	}
	
	BeginTextureMode(fbo);

	ClearBackground(BLACK);

	BeginMode2D(state.camera);
		DrawTextureEx(bg, (Vector2){0, 0}, 0.0f, bg_scale, WHITE);
	EndMode2D();

	switch (state.screen) {
	case TITLE:
		gamescreen_draw_title();
		break;
	case GAMEPLAY:
		gamescreen_draw_gameplay();
		break;
	case ENDING:
		gamescreen_draw_ending();
		break;
	}

	EndTextureMode();

	// -----

	BeginDrawing();

	DrawTexturePro(
		fbo.texture,
		(Rectangle){ 0.0f, 0.0f, (float)fbo.texture.width, (float)-fbo.texture.height },
		(Rectangle){ (GetScreenWidth() - ((float)RWIDTH*fbo_scale))*0.5f, (GetScreenHeight() - ((float)RHEIGHT*fbo_scale))*0.5f, (float)RWIDTH*fbo_scale, (float)RHEIGHT*fbo_scale },
		(Vector2){ 0, 0 },
		0.0f,
		WHITE);

	EndDrawing();
}
