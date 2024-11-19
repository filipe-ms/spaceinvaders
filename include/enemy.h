#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player.h"

typedef enum {
    LEIGO,
    ZIGZAG,
    BOOSTER,
    PAREDAO,
    BOSS
} EnemyName;

typedef struct Behavior {
	Vector2 position[10];
	Vector2 speed[10];
    int cycle;
	bool active;
	Color color;
} Behavior;

typedef struct Enemy {
    int id;
    bool active;
    Rectangle source;
    Rectangle position;
    Vector2 offset;
    Vector2 speed;
    Color color;
    float hp;
    float exp;
    Behavior behavior;
    float move_time;
    bool action_flag;
} Enemy;

void InitEnemies(Enemy* enemy);
void UpdateEnemies(Enemy* enemy, Player *player);
void DrawEnemies(Enemy* enemy);
bool CheckEnemyCollisionWithPlayer(Player player, Enemy* enemy);

void SpawnEnemies(Enemy* enemy, int amount, int id, int hp);
void SpawnRandomEnemies(Enemy* enemy, int amount, int hp);

void LoadEnemyTextures();
void UnloadEnemyTextures();


#endif