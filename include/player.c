// player.c

#include "player.h"
#include "game_constants.h"
#include "math.h"

InitShipOne(Player* player) {
    player->ship.texture_position = (Rectangle){ player->rec.x, player->rec.y, 64, 64 };
    player->ship.offset = (Vector2){ 0, 0 }; // 4, 4
    player->ship.thruster_offset = 0;
    player->ship.thruster_texture_position = (Rectangle){ player->rec.x + player->ship.thruster_offset, player->rec.y + 56, 64, 64 }; // player->rec.y + 48
    player->ship.thruster_cycle = 0;
    player->ship.speed.x = 360;
    player->ship.speed.y = 360;
}

void InitPlayer(struct Player* player) {
    player->ship.id = 0;
    player->rec.x = SCREEN_WIDTH / 2 - 32;
    player->rec.y = (SCREEN_HEIGHT - 100);
    player->rec.width = 48;
    player->rec.height = 48;

    player->color = BLACK;

    switch (player->ship.id) {
    default:
        InitShipOne(player);
    }
}

Rectangle GetPlayerRectangle() {
    if (IsKeyDown(KEY_RIGHT)) {
        Rectangle ship_texture_right = { 16, 0, 8, 8 };
        return ship_texture_right;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        Rectangle ship_texture_left = { 0, 0, 8, 8 };
        return ship_texture_left;
    }
    Rectangle ship_texture_center = { 8, 0, 8, 8 };
    return ship_texture_center;
}

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

void UpdateThrusters(struct Player* player) {
    if (IsKeyDown(KEY_RIGHT)) {
        player->ship.thruster_offset = 8;
        player->ship.thruster_cycle -= 1*GetFrameTime();
    }
    else if (IsKeyDown(KEY_LEFT)) {
        player->ship.thruster_offset = -8;
    }
    else {
        player->ship.thruster_offset = 0;
    }
    player->ship.thruster_cycle = fmod((player->ship.thruster_cycle + 10*GetFrameTime()), 4.0f);
}

void MovePlayer(struct Player* player, float delta_time) {
    if (IsKeyDown(KEY_RIGHT)) player->rec.x += player->ship.speed.x * delta_time;
    if (IsKeyDown(KEY_LEFT)) player->rec.x -= player->ship.speed.x * delta_time;
    if (IsKeyDown(KEY_UP)) player->rec.y -= player->ship.speed.y * delta_time;
    if (IsKeyDown(KEY_DOWN)) player->rec.y += player->ship.speed.y * delta_time;
}

void UpdateDrawPlayer(Player* player) {
    player->ship.texture_position = (Rectangle){ player->rec.x, player->rec.y, 64, 64 }; //(Rectangle){ player->rec.x - 4, player->rec.y - 8, 64, 64 };
    player->ship.thruster_texture_position = (Rectangle){ player->rec.x + player->ship.thruster_offset, player->rec.y + 56, 64, 64 }; //(Rectangle){ player->rec.x - 4 + player->ship.thruster_offset, player->rec.y + 48, 64, 64 };
    UpdateThrusters(player);
}

void DrawPlayer(struct Player* player) {
    DrawTexturePro(player->ship.thruster_texture, GetThrusters(player->ship.thruster_cycle), player->ship.thruster_texture_position, player->ship.offset, 0, WHITE);
    DrawTexturePro(player->ship.texture, GetPlayerRectangle(), player->ship.texture_position, player->ship.offset, 0, WHITE);
    
}

void WallBehavior(struct Player* player) {
    if (player->rec.x <= 0) player->rec.x = 0;
    if (player->rec.x + player->rec.width >= SCREEN_WIDTH) player->rec.x = SCREEN_WIDTH - player->rec.width;
    if (player->rec.y <= 0) player->rec.y = 0;
    if (player->rec.y + player->rec.height >= SCREEN_HEIGHT) player->rec.y = SCREEN_HEIGHT - player->rec.height;
}

void LoadPlayerTextures(Player *player) {
    player->ship.texture = LoadTexture("ships.png");
    player->ship.thruster_texture = LoadTexture("playerassets.png");
}

void UnloadPlayerTextures(Player *player) {
    UnloadTexture(player->ship.texture);
    UnloadTexture(player->ship.thruster_texture);
}