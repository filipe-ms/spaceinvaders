#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player.h"

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

void InitEnemies(Enemy enemy[]);
void UpdateEnemies(Enemy enemy[], int activeEnemies);
void DrawEnemies(Enemy enemy[], int activeEnemies);
bool CheckEnemyCollision(Player player, Enemy enemy[], int active_enemies);
void LoadEnemyTextures();
void UnloadEnemyTextures();

#endif // ENEMY_H
