// weapons.h

#pragma once

#include "raylib.h"  // Importando para utilizar os rectangles.
#include "player.h"  // Para definir a posição inicial do tiro
#include "enemy.h"

#ifndef WEAPONS_H
#define WEAPONS_H

#define PHOTON 0

typedef struct ActiveShoot {
    Rectangle rec;
    bool active;
} ActiveShoot;

typedef struct Weapon {
    int id;
    bool active;

    Texture texture;
    Rectangle source;

    Vector2 pivot;

    float cooldown_time_s;
    float cooldown_charge_s;
    float charge_time_modifier;

    int max_active_shoots;

    Vector2 shoot_speed;
    Color shoot_color;

    ActiveShoot shoot[50];
} Weapon;

void LoadWeaponTextures(Weapon *weapon);
void UnloadWeaponTextures(Weapon* weapon);
void InitWeapon(Weapon* weapons, Player player);
void InitWeaponShoot(ActiveShoot* shoot, Player player);
void PlayerShoot(Weapon* weapon, Player player, Enemy* enemy, int activeEnemies, int* enemiesKill, int* score);
void CheckWeaponCooldownAndShoot(Weapon* weapon, Player player);
void UpdateShootPosition(Weapon* weapon, Enemy *enemy, int active_enemies, int* enemy_kill, int* score);
void DrawWeaponShoot(Weapon weapon);
void InitPhoton(Weapon* weapon);

#endif // WEAPONS_H
