// weapons.h

#pragma once

#include "raylib.h"  // Importando para utilizar os rectangles.
#include "player.h"  // Para definir a posição inicial do tiro
#include "enemy.h"

#ifndef WEAPONS_H
#define WEAPONS_H

#define PULSE 0 // Aurea starting weapon
#define PHOTON 1 // Orion starting weapon


//--------------------------------------------------------------
//
//                         GENERIC
// 
//--------------------------------------------------------------

typedef struct Shoot {
    bool active;
    float damage;
    Rectangle position;
    Rectangle draw_position;
} Shoot;

typedef struct Weapon {
    int id;
    bool active;
    Rectangle source;
    Vector2 pivot;
    Vector2 speed;
    Color color;
    
    float damage;

    float cooldown_time_s;
    float cooldown_charge_s;
    float charge_time_modifier;
    
    int max_active_shoots;
} Weapon;

//--------------------------------------------------------------
//
//                         Pulse
// 
//--------------------------------------------------------------

typedef struct PulseShoot {
    Shoot shoot;
    int shoot_cycle;
} PulseShoot;

typedef struct Pulse {
    Weapon weapon;
    int weapon_cycle;

    Vector2 speed_1;
    Vector2 speed_2;
    Vector2 speed_3;
    float rotation_1;
    float rotation_2;
    
    PulseShoot pulse_shoot[50];
} Pulse;


// Specific
Shoot* GetPulseShoot(int index);
bool CheckPulseCollision(int index, Enemy* enemy);

//--------------------------------------------------------------
//
//                         Photon
// 
//--------------------------------------------------------------

typedef struct Photon {
	Weapon weapon;
    Shoot shoot[50];
} Photon;

// General
void InitWeapon(Player* player);
void UpdateWeapon(Player* player);
void DrawWeapon();
void LoadWeaponTextures(void);
void UnloadWeaponTextures(void);



#endif // WEAPONS_H
