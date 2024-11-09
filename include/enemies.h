// enemies.h

#include "raylib.h" // Importando para utilizar os rectangles.
#include "time_management.h"

#ifndef ENEMIES_H
#define ENEMIES_H

typedef struct Enemy {
    Rectangle rec;
    Vector2 position;
    Vector2 speed;
    bool active;
    Color color;
} Enemy;

Rectangle enemy_rectangles[5] = { // Array de texturas das naves inimigas
    { 48, 8, 8, 8 },
    { 32, 24, 8, 8 },
    { 48, 24, 8, 8 },
    { 32, 8, 8, 8 },
    { 16, 8, 8, 8 }
};

Texture enemy_texture;
Vector2 enemy_vect = { 4, 4 };

void InitEnemies(struct Enemy enemy[], int max_number_of_enemies, int screen_width, int screen_height) {
    for (int i = 0; i < max_number_of_enemies; i++)
    {
        enemy[i].rec.width = 10;
        enemy[i].rec.height = 10;
        enemy[i].rec.x = GetRandomValue(screen_width, screen_width + 1000);
        enemy[i].rec.y = GetRandomValue(0, screen_height - enemy[i].rec.height);
        enemy[i].position.x = enemy[i].rec.x;
        enemy[i].position.y = enemy[i].rec.y;
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 120;
        enemy[i].active = true;
        enemy[i].color = GRAY;
    }
}

void UpdateEnemies(struct Enemy enemy[], int activeEnemies, int screen_width, int screen_height) {
    for (int i = 0; i < activeEnemies; i++)
    {
        if (enemy[i].active)
        {
            enemy[i].rec.y += enemy[i].speed.y * GetUpdatedDelta();

            if (enemy[i].rec.y > screen_height)
            {
                enemy[i].rec.x = GetRandomValue(0, screen_width - enemy[i].rec.width);
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

void LoadEnemyTextures() {
    enemy_texture = LoadTexture("ships.png");
}

void UnloadEnemyTextures() {
    UnloadTexture(enemy_texture);
}

#endif // ENEMIES_H