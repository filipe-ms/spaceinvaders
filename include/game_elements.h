// game_elements.h

#pragma once

#include "math.h"
#include "raylib.h"  // Importando para utilizar os rectangles.
#include "player.h"  // Para definir a posição inicial do tiro
#include "time_management.h"  // Para eventos que utilizam tempo

#ifndef GAME_ELEMENTS_H
#define GAME_ELEMENTS_H

typedef struct Background {
    Texture texture;
    float position_y;
    Color color;
    float alpha;
} Background;

void InitBackground(struct Background* background);
void UpdateBackground(struct Background* background);
void UpdateAndDrawBackground(struct Background* background);
void LoadBackgroundTexture(struct Background* background);
void UnloadBackgroundTexture(struct Background* background);

#endif // GAME_ELEMENTS_H
