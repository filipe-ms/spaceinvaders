// enemies.c

#include "enemies.h"

Rectangle enemy_rectangles[5] = {
    { 48, 8, 8, 8 },
    { 32, 24, 8, 8 },
    { 48, 24, 8, 8 },
    { 32, 8, 8, 8 },
    { 16, 8, 8, 8 }
};

Texture enemy_texture;
Vector2 enemy_vect = { 4, 4 };

void InitEnemies(struct Enemy enemy[]) {
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rec.width = 10;
        enemy[i].rec.height = 10;
        enemy[i].rec.x = GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH + 1000);
        enemy[i].rec.y = GetRandomValue(0, SCREEN_HEIGHT - enemy[i].rec.height);
        enemy[i].position.x = enemy[i].rec.x;
        enemy[i].position.y = enemy[i].rec.y;
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 120;
        enemy[i].active = true;
        enemy[i].color = GRAY;
    }
}

void UpdateEnemies(struct Enemy enemy[], int activeEnemies) {
    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].rec.y += enemy[i].speed.y * GetFrameTime();

            if (enemy[i].rec.y > SCREEN_HEIGHT)
            {
                enemy[i].rec.x = GetRandomValue(0, SCREEN_WIDTH - enemy[i].rec.width);
                enemy[i].rec.y = GetRandomValue(-200, -400);
                enemy[i].position.x = enemy[i].rec.x;
                enemy[i].position.y = enemy[i].rec.y;
            }
        }
    }
}

void DrawEnemies(struct Enemy enemy[], int activeEnemies) {
    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active) {

            enemy[i].rec.height = 48;
            enemy[i].rec.width = 48;

            int texture_index = i % 5;
            DrawTexturePro(enemy_texture, enemy_rectangles[texture_index], enemy[i].rec, enemy_vect, 0, enemy[i].color);
        }
    }
}

bool CheckEnemyCollision(struct Player player, struct Enemy enemy[], int active_enemies) {
    for (int i = 0; i < active_enemies; i++)
    {
        if (CheckCollisionRecs(player.rec, enemy[i].rec)) {
            return true;
        }
    }
    return false;
}

void LoadEnemyTextures() {
    enemy_texture = LoadTexture("ships.png");
}

void UnloadEnemyTextures() {
    UnloadTexture(enemy_texture);
}
