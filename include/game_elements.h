// game_elements.h

#include "math.h"

#include "raylib.h" // Importando para utilizar os rectangles.
#include "player.h" // Para definir a posição inicial do tiro
#include "time_management.h" // Para eventos que utilizam tempo


#ifndef GAME_ELEMENTS_H
#define GAME_ELEMENTS_H

typedef struct Background {
	Texture texture;
	float position_y;
	Color color;
} Background;


void InitBackground(struct Background *background) {
	background->position_y = -1200;
	background->color = (Color){ 255, 255, 255, 170 };
}

void UpdateBackground(struct Background* background) {
	background->position_y = fmod(background->position_y + 75 * GetFrameTime(), 2400);
}

void UpdateAndDrawBackground(struct Background *background) {
	UpdateBackground(background);
	DrawTexture(background->texture, 0, background->position_y, background->color);
	DrawTexture(background->texture, 0, background->position_y - 2400, background->color);
}

void LoadBackgroundTexture(struct Background* background) {
	background->texture = LoadTexture("purplebg.png");
}

void UnloadBackgroundTexture(struct Background* background) {
	UnloadTexture(background->texture);
}


#endif // GAME_ELEMENTS_H