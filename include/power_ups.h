// power_ups.h

#pragma once

#ifndef POWER_UPS_H
#define POWER_UPS_H

#include "raylib.h"
#include "weapon.h"
#include "player.h"

typedef enum {
    // PowerUp effects
    SHOOT_COOLDOWN,
    SHOOT_DAMAGE,
    SHOOT_SIZE,

    // New weapons
    WEAPON_PULSE,
    WEAPON_PHOTON,
    WEAPON_SHOTGUN,

    // None
    NONE = 99
} PowerUpType;

typedef struct PowerUp {
    int effect;
    float value;

    Texture texture;
    char description_line_1[20];
    char description_line_2[20];
    char description_line_3[20];
    Color color;
} PowerUp;

void PowerRandomizer(void);
PowerUp UpdateLevelUpSelectMenu(bool* flag);
void DrawLevelUpSelectMenu(bool flag);
void LoadPowerUpTextures(void);
void UnloadPowerUpTextures(void);

#endif // POWER_UPS_H
