// player.h

#pragma once

#include "raylib.h" // Importando para utilizar os rectangles.

#ifndef PLAYER_H
#define PLAYER_H

#define SHIP_1 0

typedef struct Ship {
    int id;

    Texture texture;
    Rectangle texture_position;
    
    Vector2 offset;

    Texture thruster_texture;

    int thruster_offset;
    Rectangle thruster_texture_position;

    float thruster_cycle;

    Vector2 speed;

} Ship;

typedef struct Player {
    Rectangle rec;
    Color color;
    Ship ship;
} Player;

extern Texture player_texture;
extern Texture player_assets;
extern Vector2 player_vect;

void InitPlayer(struct Player* player);
Rectangle GetPlayerRectangle();
Rectangle GetThrusters(int cycle);
void UpdateThrusters(struct Player* player);
void MovePlayer(struct Player* player, float delta_time);
void WallBehavior(struct Player* player);
void UpdateDrawPlaces(struct Player* player);
void DrawPlayer(struct Player* player);
void LoadPlayerTextures();
void UnloadPlayerTextures();

#endif // PLAYER_H
