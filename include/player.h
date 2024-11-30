// player.h

#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h" // Importando para utilizar os rectangles.

typedef struct Player {
    int ship_id;
    Rectangle position;
    Vector2 center;
    int direction;
    Vector2 speed;
    float animation_cycle;
    Color color;
    float alpha;
} Player;

Rectangle GetAureaPosition();
void InitPlayer(Player* player, int ship_id);
void UpdatePlayer(Player* player);
void DrawPlayer(Player player);

#endif // PLAYER_H
