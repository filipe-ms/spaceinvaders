// player.h

#include "raylib.h" // Importando para utilizar os rectangles.

#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    Rectangle rec;
    Vector2 speed;
    Color color;
    int fire_offset;
    Rectangle ship_texture;
    Rectangle thruster_position;
    float thruster_cycle;

} Player;

Texture player_texture;
Texture player_assets;
Vector2 player_vect = { 4, 4 };

void InitPlayer(struct Player* player, int screen_width, int screen_height) {
    player->rec.x = (screen_width) / 2;
    player->rec.y = (screen_height - 100);
    player->rec.width = 48;
    player->rec.height = 48;
    player->speed.x = 360;
    player->speed.y = 360;
    player->color = BLACK;
    player->fire_offset = 0;
    player->ship_texture = (Rectangle){ player->rec.x - 4, player->rec.y - 8, 64, 64 };
    player->thruster_position = (Rectangle){ player->rec.x - 4 + player->fire_offset, player->rec.y + 48, 64, 64 };
    
}


// A nave
Rectangle GetPlayerRectangle() {
    if (IsKeyDown(KEY_RIGHT)) {
        Rectangle player_texture_right = { 16, 0, 8, 8 };
        return player_texture_right;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        Rectangle player_texture_left = { 0, 0, 8, 8 };
        return player_texture_left;
    }
    Rectangle player_texture_center = { 8, 0, 8, 8 };
    return player_texture_center;
}

// O foguinho da nave
Rectangle GetThrusters(int cycle) {
    switch (abs(cycle)) {
    case 1:
        return (Rectangle) { 40, 8, 8, 8 };
    case 2:
        return (Rectangle) { 48, 8, 8, 8 };
    case 3:
        return (Rectangle) { 56, 8, 8, 8 };
    default:
        return (Rectangle) { 64, 8, 8, 8 };
    }
}

void UpdateThrusters(struct Player *player) {
    if (IsKeyDown(KEY_RIGHT)) {
        player->fire_offset = 8;
        player->thruster_cycle -= 0.1;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        player->fire_offset = -8;
        player->thruster_cycle = fmod((player->thruster_cycle + 0.1f), 4.0f);
    }
    else {
        player->fire_offset = 0;
        player->thruster_cycle = fmod((player->thruster_cycle + 0.1f), 4.0f);
    }
}

// Inicializar o jogador
void MovePlayer(struct Player* player, float delta_time) {
    if (IsKeyDown(KEY_RIGHT)) player->rec.x += player->speed.x * delta_time;
    if (IsKeyDown(KEY_LEFT)) player->rec.x -= player->speed.x * delta_time;
    if (IsKeyDown(KEY_UP)) player->rec.y -= player->speed.y * delta_time;
    if (IsKeyDown(KEY_DOWN)) player->rec.y += player->speed.y * delta_time;
}

// Desenhar o jogador

void UpdateDrawPlaces(struct Player *player) {
    player->ship_texture = (Rectangle){ player->rec.x - 4, player->rec.y - 8, 64, 64 };
    player->thruster_position = (Rectangle){ player->rec.x - 4 + player->fire_offset, player->rec.y + 48, 64, 64 };
}

void DrawPlayer(struct Player *player) {
    UpdateDrawPlaces(player);
    UpdateThrusters(player);
    DrawTexturePro(player_texture, GetPlayerRectangle(), player->ship_texture, player_vect, 0, WHITE);
    DrawTexturePro(player_assets, GetThrusters(player->thruster_cycle), player->thruster_position, player_vect, 0, WHITE);
}

void LoadPlayerTextures() {
    player_texture = LoadTexture("ships.png");
    player_assets = LoadTexture("playerassets.png");
}

void UnloadPlayerTextures() {
    UnloadTexture(player_texture);
}

#endif // PLAYER_H