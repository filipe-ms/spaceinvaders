// enemies.h

#pragma once

#include "raylib.h"
#include "player.h"
#include "game_constants.h"

#ifndef ENEMIES_H
#define ENEMIES_H

typedef struct Enemy {
    Rectangle rec;
    Vector2 position;
    Vector2 speed;
    bool active;
    Color color;
} Enemy;

extern Rectangle enemy_rectangles[5];
extern Texture enemy_texture;
extern Vector2 enemy_vect;

void InitEnemies(struct Enemy enemy[]);
void UpdateEnemies(struct Enemy enemy[], int activeEnemies);
void DrawEnemies(struct Enemy enemy[], int activeEnemies);
bool CheckEnemyCollision(struct Player player, struct Enemy enemy[], int active_enemies);
void LoadEnemyTextures();
void UnloadEnemyTextures();

#endif // ENEMIES_H