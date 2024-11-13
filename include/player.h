// player.h

#pragma once

#include "raylib.h" // Importando para utilizar os rectangles.

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    int ship_id;
    Rectangle position;
    int direction;
    Vector2 speed;
    float animation_cycle;
    Color color;
    float alpha;
} Player;

void InitPlayer(Player* player, int ship_id);
void UpdatePlayer(Player* player);
void DrawPlayer(Player player);

#endif // PLAYER_H
