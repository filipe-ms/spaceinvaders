// game_behavior.h

#include "raylib.h"
#include "player.h"
#include "enemies.h"

#ifndef GAME_BEHAVIOR_H
#define GAME_BEHAVIOR_H

// PLAYER-RELATED EVENTS

void WallBehavior(struct Player *player, int screen_width, int screen_height) {
    if (player->rec.x <= 0) player->rec.x = 0;
    if (player->rec.x + player->rec.width >= screen_width) player->rec.x = screen_width - player->rec.width;
    if (player->rec.y <= 0) player->rec.y = 0;
    if (player->rec.y + player->rec.height >= screen_height) player->rec.y = screen_height - player->rec.height;
}

void CheckEnemyCollision(struct Player *player, struct Enemy enemy[], int active_enemies, bool *game_over) {
    for (int i = 0; i < active_enemies; i++)
    {
        if (CheckCollisionRecs(player->rec, enemy[i].rec)) {
            *game_over = true;
        }
    }
}

#endif // GAME_BEHAVIOR_H