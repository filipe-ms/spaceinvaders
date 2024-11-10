// weapons.h

#pragma once

#include "raylib.h"  // Importando para utilizar os rectangles.
#include "player.h"  // Para definir a posição inicial do tiro
#include "enemies.h"

#ifndef WEAPONS_H
#define WEAPONS_H

#define PHOTON 0
#define NUMBER_OF_WEAPONS 1

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

    struct ActiveShoot shoot[50];
} Weapon;

void LoadWeaponTextures(Weapon *weapon);
void UnloadWeaponTextures(Weapon* weapon);
void InitWeapon(struct Weapon* weapons, struct Player player);
void InitWeaponShoot(struct ActiveShoot* shoot, struct Player player);
void PlayerShoot(Weapon* weapon, Player player, Enemy* enemy, int activeEnemies, int* enemiesKill, int* score);
void CheckWeaponCooldownAndShoot(struct Weapon* weapon, struct Player player);
void UpdateShootPosition(struct Weapon* weapon, struct Enemy enemy[], int active_enemies, int* enemy_kill, int* score);
void DrawWeaponShoot(struct Weapon weapon);
void InitPhoton(struct Weapon* weapon);


#endif // WEAPONS_H
