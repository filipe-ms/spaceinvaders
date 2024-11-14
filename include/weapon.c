// weapon.c

#include "weapon.h"
#include "draw_object.h"
#include "raymath.h"
#include "player.h"
#include <corecrt_math_defines.h>
#include <math.h>

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

Texture texture;

static float cooldown_modifier = 0.0f;
static float damage_modifier = 0.0f;
static float size_modifier = 1.0f;

void IncrementCooldownModifier(float value) {
	cooldown_modifier += value;
}

void IncrementDamageModifier(float value) {
	damage_modifier += value;
}

void IncrementSizeModifier(float value) {
	size_modifier += value;
}


//--------------------------------------------------------------
//
//                         PULSE
// 
//--------------------------------------------------------------

Pulse pulse;
float speed_factor = 5.0f;

InitPulse() {
    pulse.weapon.id = PULSE;
    pulse.weapon.active = false;
    
    pulse.weapon.source = (Rectangle){ 42, 0, 8, 8 };
    pulse.weapon.offset = (Vector2){ 0, -32 };
    pulse.weapon.pivot = (Vector2){ 0, 0 };
    pulse.weapon.color = WHITE;

    pulse.weapon.damage = 1.0f;

    pulse.weapon.cooldown_time_s = 1.0f / 3.0f;
    pulse.weapon.cooldown_charge_s = 0;
    pulse.weapon.charge_time_modifier = 1;

    pulse.weapon.max_active_shoots = 50;
	
    pulse.rotation = 15;

    pulse.weapon_cycle = -1;

	pulse.weapon.speed = (Vector2){ 0, -500 }; // Baseline speed

    for (int i = 0; i < 50; i++) {
		pulse.pulse_shoot[i].shoot.active = false;
		pulse.pulse_shoot[i].shoot.damage = pulse.weapon.damage;
    }
}

void InitPulseShoot(Player *player) {

    for (int i = 0; i < 50; i++) {
        if (pulse.pulse_shoot[i].shoot.active) continue;
        
        pulse.pulse_shoot[i].shoot.active = true;

        pulse.pulse_shoot[i].shoot.damage = pulse.weapon.damage + damage_modifier;

        pulse.pulse_shoot[i].shoot.draw_position.height = 64 * size_modifier;
        pulse.pulse_shoot[i].shoot.draw_position.width = 64 * size_modifier;

        pulse.pulse_shoot[i].shoot.position.width = 32 * size_modifier;
        pulse.pulse_shoot[i].shoot.position.height = 32 * size_modifier;

        Vector2 shoot_position = { player->position.x + player->position.width / 2, player->position.y + player->position.height / 2 };
        Vector2 rotation_offset = Vector2Rotate(pulse.weapon.offset, degToRad(pulse.weapon_cycle * pulse.rotation + M_PI_2));
            
        pulse.pulse_shoot[i].shoot.position.x = rotation_offset.x + shoot_position.x - pulse.pulse_shoot[i].shoot.position.width / 2;
        pulse.pulse_shoot[i].shoot.position.y = rotation_offset.y + shoot_position.y - pulse.pulse_shoot[i].shoot.position.height / 2;
        
        pulse.pulse_shoot[i].shoot.speed = Vector2Rotate(pulse.weapon.speed, degToRad(pulse.weapon_cycle * pulse.rotation + M_PI_2));
        
        pulse.pulse_shoot[i].shoot_cycle = pulse.weapon_cycle;

        pulse.weapon_cycle--;
        if (pulse.weapon_cycle == -2) pulse.weapon_cycle = 1;
            
        return;
    }
}

void UpdatePulseShoot() {
    for (int i = 0; i < 50; i++) {
        if (!pulse.pulse_shoot[i].shoot.active) continue;

        Vector2 offset = (Vector2){ pulse.weapon.offset.x / 2, pulse.weapon.offset.y / 2 };
        Vector2 rotationOffset = Vector2Rotate(offset, degToRad(pulse.pulse_shoot[i].shoot_cycle * pulse.rotation + M_PI_2));
        
        pulse.pulse_shoot[i].shoot.position.x += pulse.pulse_shoot[i].shoot.speed.x * GetFrameTime();
        pulse.pulse_shoot[i].shoot.position.y += pulse.pulse_shoot[i].shoot.speed.y * GetFrameTime();

        pulse.pulse_shoot[i].shoot.draw_position.x = pulse.pulse_shoot[i].shoot.position.x + rotationOffset.x;
        pulse.pulse_shoot[i].shoot.draw_position.y = pulse.pulse_shoot[i].shoot.position.y + rotationOffset.y;

        if (pulse.pulse_shoot[i].shoot.position.y < -80) {
            pulse.pulse_shoot[i].shoot.active = false;
        }
    }
}

void UpdatePulse(Player *player) {
	if (!pulse.weapon.active) return;

    UpdatePulseShoot();

    pulse.weapon.cooldown_charge_s += (pulse.weapon.charge_time_modifier + cooldown_modifier) * GetFrameTime();

    if (pulse.weapon.cooldown_charge_s >= pulse.weapon.cooldown_time_s) {
		InitPulseShoot(player);
        pulse.weapon.cooldown_charge_s -= pulse.weapon.cooldown_time_s;
    }
}

void DrawPulseShoot() {
    for (int i = 0; i < 50; i++) {
        if (!pulse.pulse_shoot[i].shoot.active) continue;
        DrawTexturePro(texture, pulse.weapon.source, pulse.pulse_shoot[i].shoot.draw_position, pulse.weapon.pivot, 15 * pulse.pulse_shoot[i].shoot_cycle, WHITE);
    }
}

Shoot* GetPulseShoot(int index) {
    return &pulse.pulse_shoot[index].shoot;
}

bool IsPulseActive(void) {
	return pulse.weapon.active;
}


//--------------------------------------------------------------
//
//                         PHOTON
// 
//--------------------------------------------------------------

Photon photon;

void InitPhoton(void) {

    photon.weapon.id = PHOTON;
    photon.weapon.active = false;

    photon.weapon.source = (Rectangle){ 0, 8, 8, 8 };
    photon.weapon.pivot = (Vector2){ 0, 0 };

    photon.weapon.damage = 1.0f;

    photon.weapon.cooldown_time_s = (float)(1.0f / 2.0f);
    photon.weapon.cooldown_charge_s = 0;
    photon.weapon.charge_time_modifier = 1;

    photon.weapon.max_active_shoots = 50;

    photon.weapon.speed = (Vector2){ 0, 720 };
    photon.weapon.color = RED;

    for (int i = 0; i < photon.weapon.max_active_shoots; ++i) {
        photon.shoot[i].active = false;
        photon.shoot[i].damage = photon.weapon.damage;

        photon.shoot[i].position.width = 36;
        photon.shoot[i].position.height = 36;

        photon.shoot[i].speed = photon.weapon.speed;
    }
}

void InitPhotonShoot(Player *player) {
    for (int i = 0; i < photon.weapon.max_active_shoots; i++) {
		if (photon.shoot[i].active) continue;

        photon.shoot[i].active = true;
        photon.shoot[i].position.x = (player->center.x)-18;
        photon.shoot[i].position.y = (player->center.y)-18;
		photon.shoot[i].position.width = 36 * size_modifier;
		photon.shoot[i].position.height = 36 * size_modifier;

		photon.shoot[i].speed = photon.weapon.speed;
		photon.shoot[i].damage = photon.weapon.damage + damage_modifier;

        
        break;
    }
}


void UpdatePhotonCooldownAndShoot(Player* player) {
	if (!photon.weapon.active) return;

	photon.weapon.cooldown_charge_s += (photon.weapon.charge_time_modifier + cooldown_modifier) * GetFrameTime();

	if (photon.weapon.cooldown_charge_s >= photon.weapon.cooldown_time_s) {
		InitPhotonShoot(player);
        photon.weapon.cooldown_charge_s -= photon.weapon.cooldown_time_s;
    }
}

void UpdatePhotonShootPosition() {
    for (int i = 0; i < 50; i++) {
        if (!photon.shoot[i].active) continue;

        if (photon.shoot[i].position.y < -80) {
            photon.shoot[i].active = false;
            continue;
        }

        photon.shoot[i].position.y -= photon.weapon.speed.y * GetFrameTime();
    }
}

void DrawPhotonShoot() {
    for (int i = 0; i < 50; i++) {
        if (photon.shoot[i].active) {
            DrawTexturePro(texture, photon.weapon.source, photon.shoot[i].position, photon.weapon.pivot, 0, WHITE);
        }
    }
}

bool IsPhotonActive() {
	return photon.weapon.active;
}

void UpdatePhoton(Player* player) {
    UpdatePhotonCooldownAndShoot(player);
    UpdatePhotonShootPosition();
}

Shoot* GetPhotonShoot(int index) {
    return &photon.shoot[index];
}

//--------------------------------------------------------------

void InitAllWeapons() {
    InitPulse();
    InitPhoton();
}

void InitWeapon(Player* player) {
    cooldown_modifier = 0.0f;
    damage_modifier = 0.0f;
    size_modifier = 1.0f;

    InitAllWeapons();

    if (player->ship_id == AUREA) pulse.weapon.active = true;
    if (player->ship_id == ORION) photon.weapon.active = true;
    if (player->ship_id == NEBULA) photon.weapon.active = true;
}

void UpdateWeapon(Player *player) {
    UpdatePhoton(player);
    UpdatePulse(player);
}

void DrawWeapon() {
    DrawPulseShoot();
    DrawPhotonShoot();
    
}

void LoadWeaponTextures(void) {
    texture = LoadTexture("weapons.png");
}

void UnloadWeaponTextures(void) {
    UnloadTexture(texture);
}




