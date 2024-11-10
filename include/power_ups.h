// power_ups.h

#pragma once

#include "raylib.h"  // Importando para utilizar os rectangles.
#include "player.h"
#include "weapons.h"

#ifndef POWER_UPS_H
#define POWER_UPS_H

// Shoot Rate Power Up
typedef struct PowerUpShootRate {
    Rectangle rec;  // Posição e tamanho do item
    bool active;    // Estado ativo/inativo do item
    Color color;    // Cor do item
} PowerUpShootRate;

void InitShootRatePowerUp(struct PowerUpShootRate* power);
void SpawnShootRatePowerUp(struct PowerUpShootRate* power);
void DrawPowerUps(struct PowerUpShootRate power);
void UpdatePowerUp(struct PowerUpShootRate* power, struct Weapon* weapon, struct Player player);

#endif // POWER_UPS_H
