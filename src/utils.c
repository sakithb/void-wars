#include "../include/utils.h"

void healthbar_draw(Vector2 position, float health) {
	Vector2 start = {position.x - 16, position.y + 24};
	Vector2 end = {(position.x - 16) + (32 * health), position.y + 24};
	Color color = health > 0.8 ? GREEN : health > 0.6 ? LIME : health > 0.4 ? YELLOW : health > 0.2 ? ORANGE : RED;

	DrawLineV(start, end, color);
}
