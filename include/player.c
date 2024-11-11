// player.c

#include "player.h"
#include "game_constants.h"
#include "draw_object.h"
#include "math.h"

// Possible Ships
Orion orion;

void InitPlayer(Player *player, int ship_id) {
    player->ship = ship_id;

    player->position.x = SCREEN_WIDTH / 2 - 32;
    player->position.y = (SCREEN_HEIGHT - 100);

    player->position.width = 48;
    player->position.height = 48;

    player->direction = CENTER;

    player->speed.x = 360;
    player->speed.y = 360;

    player->animation_cycle = 0;

    player->color = WHITE;
    player->alpha = 1.0f;
}

// Update related

void UpdatePlayerDirection(Player* player) {
    if (IsKeyDown(KEY_RIGHT)) player->direction = RIGHT;
    else if (IsKeyDown(KEY_LEFT)) player->direction = LEFT;
    else player->direction = CENTER;
}

void WallBehavior(Player* player) {
    if (player->position.x <= 0) player->position.x = 0;
    if (player->position.x + player->position.width >= SCREEN_WIDTH) player->position.x = SCREEN_WIDTH - player->position.width;
    if (player->position.y <= 0) player->position.y = 0;
    if (player->position.y + player->position.height >= SCREEN_HEIGHT) player->position.y = SCREEN_HEIGHT - player->position.height;
}

void UpdatePlayerPosition(Player* player) {
    if (IsKeyDown(KEY_RIGHT)) player->position.x += player->speed.x * GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) player->position.x -= player->speed.x * GetFrameTime();
    if (IsKeyDown(KEY_UP)) player->position.y -= player->speed.y * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) player->position.y += player->speed.y * GetFrameTime();
    WallBehavior(player);
}

void UpdatePlayerAnimationCycle(Player* player) {
    player->animation_cycle += 0.2f * GetFrameTime();
    if (player->animation_cycle > 1.0f) player->animation_cycle -= 1.0f;
}

int GetThrusterAnimationCycle(Player *player) {
    if (IsKeyDown(KEY_RIGHT)) {
        if (player->animation_cycle < 0.25f) return 4;
        if (player->animation_cycle < 0.5f) return 3;
        if (player->animation_cycle < 0.75f) return 2;
        return 1;
    }
    else {
        if (player->animation_cycle < 0.25f) return 1;
        if (player->animation_cycle < 0.5f) return 2;
        if (player->animation_cycle < 0.75f) return 3;
        return 4;
    }
}

void UpdateOrion(Player *player) {
    orion.destination = player->position;
    orion.direction = player->direction;
    orion.thruster_cycle = GetThrusterAnimationCycle(player);
    orion.color = player->color;
    orion.alpha = player->alpha;
}

void UpdatePlayer(Player *player) {
    // General updates
    UpdatePlayerDirection(player);
    UpdatePlayerPosition(player);
    UpdatePlayerAnimationCycle(player);

    // Ship updates
    if (player->ship == ORION) UpdateOrion(player);
}

// Draw related
void DrawPlayer(Player player) {
    if (player.ship == ORION) DrawOrion(&orion);
}