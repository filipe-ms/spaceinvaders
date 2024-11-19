// weapon.h

#pragma once

#ifndef WEAPON_H
#define WEAPON_H

#include "raylib.h"  // Importando para utilizar os rectangles.
#include "player.h"  // Para definir a posição inicial do tiro
#include "enemy.h"

#define PULSE 0 // Aurea starting weapon
#define PHOTON 1 // Orion starting weapon
#define SHOTGUN 2 // Nebula starting weapon


//--------------------------------------------------------------
//
//                         GENERIC
// 
//--------------------------------------------------------------

typedef struct Shoot {
    bool active;
    float damage;
	Vector2 speed;
    Rectangle position;
    Rectangle draw_position;
} Shoot;

typedef struct Weapon {
    int id;
    bool active;
    Rectangle source;
    Vector2 offset;
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

    Vector2 speed;

    float rotation;
    
    PulseShoot pulse_shoot[50];
} Pulse;


// Specific
Shoot* GetPulseShoot(int index);
bool IsPulseActive(void);
void ActivatePulse(void);

//--------------------------------------------------------------
//
//                         Photon
// 
//--------------------------------------------------------------

typedef struct Photon {
	Weapon weapon;
    Shoot shoot[50];
} Photon;

Shoot* GetPhotonShoot(int index);
bool IsPhotonActive(void);
void ActivatePhoton(void);

//--------------------------------------------------------------
//
//                         Shotgun
// 
//--------------------------------------------------------------

typedef struct ShotgunShoot {
	Shoot shoot;
    Rectangle source;
    float lifespan;
    float orientation;
    float alpha;
} ShotgunShoot;

typedef struct Shotgun {
	Weapon weapon;
    float arc;
	ShotgunShoot shotgun_shoot[50];
} Shotgun;

Shoot* GetShotgunShoot(int index);
bool IsShotgunActive(void);
void ActivateShotgun(void);

// General
void InitWeapon(Player* player);
void UpdateWeapon(Player* player);
void DrawWeapon();
void LoadWeaponTextures(void);
void UnloadWeaponTextures(void);

// Power Modifiers
void IncrementCooldownModifier(float value);
void IncrementDamageModifier(float value);
void IncrementSizeModifier(float value);

#endif // WEAPON_H
