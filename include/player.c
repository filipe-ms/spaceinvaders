// player.c

#include "player.h"
#include "common.h"
#include "draw_object.h"
#include "math.h"

// Possible Ships
Orion orion;
Aurea aurea;
Nebula nebula;

void InitPlayer(Player *player, int ship_id) {
    player->ship_id = ship_id;

    player->center.x = player->position.x = SCREEN_WIDTH / 2;
    player->center.y = player->position.y = (SCREEN_HEIGHT - 100);

    player->position.width = 48;
    player->position.height = 48;
  
    player->position.x = player->center.x + player->position.width / 2;
    player->position.y = player->center.y + player->position.height / 2;

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

float SI_Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void WallBehavior(Player* player) {
    player->position.x = SI_Clamp(player->position.x, 16, SCREEN_WIDTH - player->position.width-16);
    
    if (player->position.y <= player->position.height) player->position.y = player->position.height;
    if (player->position.y + player->position.height >= SCREEN_HEIGHT) player->position.y = SCREEN_HEIGHT - player->position.height;
}

void UpdatePlayerPosition(Player* player) {
    if (IsKeyDown(KEY_RIGHT)) player->position.x += player->speed.x * GetFrameTime();
    if (IsKeyDown(KEY_LEFT)) player->position.x -= player->speed.x * GetFrameTime();
    if (IsKeyDown(KEY_UP)) player->position.y -= player->speed.y * GetFrameTime();
    if (IsKeyDown(KEY_DOWN)) player->position.y += player->speed.y * GetFrameTime();
    WallBehavior(player);
    player->center.x = (player->position.x + player->position.width / 2);
    player->center.y = (player->position.y + player->position.height / 2);
}

void UpdatePlayerAnimationCycle(Player* player) {
    player->animation_cycle += 1.0f * GetFrameTime();
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

// Ship updates

Rectangle GetAureaPosition() {
    return aurea.destination;
}

void UpdateAurea(Player* player) {

    aurea.destination.x = player->position.x - 8;
    aurea.destination.y = player->position.y - 8;


    aurea.destination.height = 64;
    aurea.destination.width = 64;
    aurea.direction = player->direction;
    aurea.thruster_cycle = GetThrusterAnimationCycle(player);
    aurea.color = player->color;
    aurea.alpha = player->alpha;
}

void UpdateOrion(Player *player) {
    orion.destination = player->position;
    orion.destination.height = 64;
    orion.destination.width = 64;
    orion.direction = player->direction;
    orion.thruster_cycle = GetThrusterAnimationCycle(player);
    orion.color = player->color;
    orion.alpha = player->alpha;
}

void UpdateNebula(Player* player) {
	nebula.destination = player->position;
	nebula.destination.height = 64;
	nebula.destination.width = 64;
	nebula.direction = player->direction;
	nebula.thruster_cycle = GetThrusterAnimationCycle(player);
	nebula.color = player->color;
	nebula.alpha = player->alpha;
}

void UpdatePlayer(Player *player) {
    // General updates
    UpdatePlayerDirection(player);
    UpdatePlayerPosition(player);
    UpdatePlayerAnimationCycle(player);

    // Ship updates
    if (player->ship_id == AUREA) UpdateAurea(player);
    if (player->ship_id == ORION) UpdateOrion(player);
	if (player->ship_id == NEBULA) UpdateNebula(player);

}

// Draw related
void DrawPlayer(Player player) {
    if (player.ship_id == AUREA) DrawAurea(&aurea);
    if (player.ship_id == ORION) DrawOrion(&orion);
    if (player.ship_id == NEBULA) DrawNebula(&nebula);
}