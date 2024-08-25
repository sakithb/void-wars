#include "raylib.h"
#include "../include/contants.h"
#include "../include/screens.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>

EM_JS(int, GetWindowInnerWidthC, (), { return window.innerWidth; });
EM_JS(int, GetWindowInnerHeightC, (), { return window.innerHeight; });
#endif

RenderTexture fb;
Texture bg;
float bg_scale;
State state;

int win_width = 1920;
int win_height = 1080;

void game_loop();

int main() {
#if defined(PLATFORM_WEB)
	win_width = GetWindowInnerWidthC();
	win_height = GetWindowInnerHeightC();
#endif

	InitWindow(win_width, win_height, "Void Wars");
	
	fb = LoadRenderTexture(RWIDTH, RHEIGHT);
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
	UnloadRenderTexture(fb);

	CloseWindow();
}

void game_loop() {
	float fbo_scale = MIN((float)win_width/RWIDTH, (float)win_height/RHEIGHT);

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
	
	BeginTextureMode(fb);

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
		fb.texture,
		(Rectangle){ 0.0f, 0.0f, (float)fb.texture.width, (float)-fb.texture.height },
		(Rectangle){ (win_width - ((float)RWIDTH*fbo_scale))*0.5f, (win_height - ((float)RHEIGHT*fbo_scale))*0.5f, (float)RWIDTH*fbo_scale, (float)RHEIGHT*fbo_scale },
		(Vector2){ 0, 0 },
		0.0f,
		WHITE);

	EndDrawing();
}
