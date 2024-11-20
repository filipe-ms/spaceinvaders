// weapon.c

#define PI 3.14159265358979323846
#define degToRad(angleInDegrees) ((angleInDegrees) * PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / PI)


#include "weapon.h"
#include "draw_object.h"
#include "raymath.h"
#include "player.h"
#include <math.h>




// Power up textures
Texture texture;

// Power up values
static float cooldown_modifier = 0.0f;
static float damage_modifier = 0.0f;
static float size_modifier = 1.0f;

//--------------------------------------------------------------
//
//                         PULSE
// 
//--------------------------------------------------------------

Pulse pulse;
float speed_factor = 5.0f;

static void InitPulse(void) {
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

static void InitPulseShoot(Player *player) {

    for (int i = 0; i < 50; i++) {
        if (pulse.pulse_shoot[i].shoot.active) continue;
        
        pulse.pulse_shoot[i].shoot.active = true;

        pulse.pulse_shoot[i].shoot.damage = pulse.weapon.damage + damage_modifier;

        pulse.pulse_shoot[i].shoot.draw_position.height = 64 * size_modifier;
        pulse.pulse_shoot[i].shoot.draw_position.width = 64 * size_modifier;

        pulse.pulse_shoot[i].shoot.position.height = 32 * size_modifier;
        pulse.pulse_shoot[i].shoot.position.width = 32 * size_modifier;
        
        Vector2 rotation_offset = Vector2Rotate(pulse.weapon.offset, (float)(degToRad(pulse.weapon_cycle * pulse.rotation)));
            
        pulse.pulse_shoot[i].shoot.position.x = rotation_offset.x + player->center.x - pulse.pulse_shoot[i].shoot.position.width / 2.0f;
        pulse.pulse_shoot[i].shoot.position.y = rotation_offset.y + player->center.y - pulse.pulse_shoot[i].shoot.position.height / 2.0f;
        
        pulse.pulse_shoot[i].shoot.speed = Vector2Rotate(pulse.weapon.speed, (float)(degToRad(pulse.weapon_cycle * pulse.rotation)));
        
        pulse.pulse_shoot[i].shoot_cycle = pulse.weapon_cycle;

        pulse.weapon_cycle--;
        if (pulse.weapon_cycle == -2) pulse.weapon_cycle = 1;
            
        break;
    }
}

static void UpdatePulseShoot() {
    for (int i = 0; i < 50; i++) {
        if (!pulse.pulse_shoot[i].shoot.active) continue;

        Vector2 offset = (Vector2){ pulse.weapon.offset.x / 2, pulse.weapon.offset.y / 2 };
        Vector2 rotationOffset = Vector2Rotate(offset, (float)(degToRad(pulse.pulse_shoot[i].shoot_cycle * pulse.rotation)));
        
        pulse.pulse_shoot[i].shoot.position.x += pulse.pulse_shoot[i].shoot.speed.x * GetFrameTime();
        pulse.pulse_shoot[i].shoot.position.y += pulse.pulse_shoot[i].shoot.speed.y * GetFrameTime();

        pulse.pulse_shoot[i].shoot.draw_position.x = pulse.pulse_shoot[i].shoot.position.x + rotationOffset.x;
        pulse.pulse_shoot[i].shoot.draw_position.y = pulse.pulse_shoot[i].shoot.position.y + rotationOffset.y;

        if (pulse.pulse_shoot[i].shoot.position.y < -80) {
            pulse.pulse_shoot[i].shoot.active = false;
        }
    }
}

static void UpdatePulse(Player *player) {
	if (!pulse.weapon.active) return;

    pulse.weapon.cooldown_charge_s += (pulse.weapon.charge_time_modifier + cooldown_modifier) * GetFrameTime();

    if (pulse.weapon.cooldown_charge_s >= pulse.weapon.cooldown_time_s) {
		InitPulseShoot(player);
        pulse.weapon.cooldown_charge_s -= pulse.weapon.cooldown_time_s;
    }
    
    UpdatePulseShoot();
}

static void DrawPulseShoot() {
    for (int i = 0; i < 50; i++) {
        if (!pulse.pulse_shoot[i].shoot.active) continue;
        DrawTexturePro(texture, pulse.weapon.source, pulse.pulse_shoot[i].shoot.draw_position, pulse.weapon.pivot, 15.0f * pulse.pulse_shoot[i].shoot_cycle, WHITE);
    }
}

Shoot* GetPulseShoot(int index) {
    return &pulse.pulse_shoot[index].shoot;
}

bool IsPulseActive(void) {
	return pulse.weapon.active;
}

void ActivatePulse(void) {
    pulse.weapon.active = true;
}

//--------------------------------------------------------------
//
//                         PHOTON
// 
//--------------------------------------------------------------

Photon photon;

static void InitPhoton(void) {

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

static void InitPhotonShoot(Player *player) {
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

static void UpdatePhotonCooldownAndShoot(Player* player) {
	if (!photon.weapon.active) return;

	photon.weapon.cooldown_charge_s += (photon.weapon.charge_time_modifier + cooldown_modifier) * GetFrameTime();

	if (photon.weapon.cooldown_charge_s >= photon.weapon.cooldown_time_s) {
		InitPhotonShoot(player);
        photon.weapon.cooldown_charge_s -= photon.weapon.cooldown_time_s;
    }
}

static void UpdatePhotonShootPosition() {
    for (int i = 0; i < 50; i++) {
        if (!photon.shoot[i].active) continue;

        if (photon.shoot[i].position.y < -80) {
            photon.shoot[i].active = false;
            continue;
        }

        photon.shoot[i].position.y -= photon.weapon.speed.y * GetFrameTime();
    }
}

static void DrawPhotonShoot() {
    for (int i = 0; i < 50; i++) {
        if (photon.shoot[i].active) {
            DrawTexturePro(texture, photon.weapon.source, photon.shoot[i].position, photon.weapon.pivot, 0, WHITE);
        }
    }
}

static void UpdatePhoton(Player* player) {
    UpdatePhotonCooldownAndShoot(player);
    UpdatePhotonShootPosition();
}

Shoot* GetPhotonShoot(int index) {
    return &photon.shoot[index];
}

bool IsPhotonActive(void) {
	return photon.weapon.active;
}

void ActivatePhoton(void) {
    photon.weapon.active = true;
}

//--------------------------------------------------------------
//
//                         SHOTGUN
// 
//--------------------------------------------------------------

Shotgun shotgun;

static void InitShotgun(void) {
    shotgun.weapon.id = SHOTGUN;
    shotgun.weapon.active = false;

    shotgun.weapon.offset = (Vector2){ 0, -32 };
    shotgun.weapon.pivot = (Vector2){ 4, 4 };

    shotgun.weapon.color = WHITE;

    shotgun.weapon.damage = 0.5f;

    shotgun.weapon.cooldown_time_s = 1.0f / 1.0f;

    shotgun.weapon.cooldown_charge_s = 0;
    shotgun.weapon.charge_time_modifier = 1;

    shotgun.weapon.max_active_shoots = 50;

    shotgun.arc = 45;

    shotgun.weapon.speed = (Vector2){ 0, -1000 }; // Baseline speed



    for (int i = 0; i < 50; i++) {
        shotgun.shotgun_shoot[i].shoot.active = false;
        shotgun.shotgun_shoot[i].shoot.damage = shotgun.weapon.damage;
    }
}

static void InitShotgunShoot(Player* player) {
    float lifespan[6] = { 0 };
    int shells = GetRandomValue(0, 3);
    for (int i = 0; i < 3 + shells; i++) {
        lifespan[i] = (float)(GetRandomValue(1, 3) / 10.0f);
    }

    for (int j = 0; j < 3 + shells; j++) {
        for (int i = 0; i < 50; i++) {
            if (shotgun.shotgun_shoot[i].shoot.active) continue;

            shotgun.shotgun_shoot[i].shoot.active = true;
            shotgun.shotgun_shoot[i].shoot.damage = shotgun.weapon.damage + damage_modifier / 2; // Balance

            shotgun.shotgun_shoot[i].shoot.draw_position.height = 64 * size_modifier;
            shotgun.shotgun_shoot[i].shoot.draw_position.width = 64 * size_modifier;

            shotgun.shotgun_shoot[i].shoot.position.height = 32 * size_modifier;
            shotgun.shotgun_shoot[i].shoot.position.width = 32 * size_modifier;

            float draw_angle = GetRandomValue(-45, 45);
            float orientation = degToRad(draw_angle);

			shotgun.shotgun_shoot[i].orientation = draw_angle;
            Vector2 rotation_offset = Vector2Rotate(shotgun.weapon.offset, orientation);

            shotgun.shotgun_shoot[i].shoot.position.x = rotation_offset.x + player->center.x - shotgun.shotgun_shoot[i].shoot.position.width / 2.0f;
            shotgun.shotgun_shoot[i].shoot.position.y = rotation_offset.y + player->center.y - shotgun.shotgun_shoot[i].shoot.position.height / 2.0f;


            Vector2 speed = { 0, shotgun.weapon.speed.y + GetRandomValue(0, -500) };

            shotgun.shotgun_shoot[i].lifespan = lifespan[j];
            shotgun.shotgun_shoot[i].alpha = lifespan[j];

            if (speed.y < -1300) {
                shotgun.shotgun_shoot[i].source = (Rectangle){ 16, 0, 8, 8 };
            }
            else {
                shotgun.shotgun_shoot[i].source = (Rectangle) { 24, 0, 8, 8 };
            }

            shotgun.shotgun_shoot[i].shoot.speed = Vector2Rotate(speed, orientation);

            break;
        }
    }
}

static void UpdateShotgunShoot() {
    for (int i = 0; i < 50; i++) {
        if (!shotgun.shotgun_shoot[i].shoot.active) continue;

        Vector2 offset = (Vector2){ shotgun.weapon.offset.y / 2, shotgun.weapon.offset.y / 2 };
        Vector2 rotation_offset = Vector2Rotate(offset, (float)(degToRad(shotgun.shotgun_shoot[i].orientation)));

        shotgun.shotgun_shoot[i].shoot.position.x += shotgun.shotgun_shoot[i].shoot.speed.x * GetFrameTime();
        shotgun.shotgun_shoot[i].shoot.position.y += shotgun.shotgun_shoot[i].shoot.speed.y * GetFrameTime();

        shotgun.shotgun_shoot[i].shoot.draw_position.x = shotgun.shotgun_shoot[i].shoot.position.x + rotation_offset.x;
        shotgun.shotgun_shoot[i].shoot.draw_position.y = shotgun.shotgun_shoot[i].shoot.position.y + rotation_offset.y;

		shotgun.shotgun_shoot[i].lifespan -= GetFrameTime();
        shotgun.shotgun_shoot[i].alpha = shotgun.shotgun_shoot[i].lifespan;

        if (shotgun.shotgun_shoot[i].shoot.position.y < -80 || shotgun.shotgun_shoot[i].lifespan <= 0) {
            shotgun.shotgun_shoot[i].shoot.active = false;
            shotgun.shotgun_shoot[i].lifespan = 0;
        }
    }
}


static void UpdateShotgun(Player* player) {
    if (!shotgun.weapon.active) return;

    shotgun.weapon.cooldown_charge_s += (shotgun.weapon.charge_time_modifier + cooldown_modifier) * GetFrameTime();

    if (shotgun.weapon.cooldown_charge_s >= shotgun.weapon.cooldown_time_s) {
        InitShotgunShoot(player);
        shotgun.weapon.cooldown_charge_s -= shotgun.weapon.cooldown_time_s;
    }

    UpdateShotgunShoot();
}

static void DrawShotgunShoot() {
    for (int i = 0; i < 50; i++) {
        if (!shotgun.shotgun_shoot[i].shoot.active) continue;
        DrawTexturePro(texture, shotgun.shotgun_shoot[i].source, shotgun.shotgun_shoot[i].shoot.draw_position, shotgun.weapon.pivot, shotgun.shotgun_shoot[i].orientation, WHITE);
    }
}

Shoot* GetShotgunShoot(int index) {
    return &shotgun.shotgun_shoot[index].shoot;
}

bool IsShotgunActive(void) {
    return shotgun.weapon.active;
}

void ActivateShotgun(void) {
    shotgun.weapon.active = true;
}


//--------------------------------------------------------------
//
//                         POWER UPS
// 
//--------------------------------------------------------------

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
//                         OTHERS
// 
//--------------------------------------------------------------

static void InitAllWeapons(void) {
    InitPulse();
    InitPhoton();
    InitShotgun();
}

void InitWeapon(Player* player) {
    cooldown_modifier = 0.0f;
    damage_modifier = 0.0f;
    size_modifier = 1.0f;

    InitAllWeapons();

    if (player->ship_id == AUREA) pulse.weapon.active = true;
    if (player->ship_id == ORION) photon.weapon.active = true;
    if (player->ship_id == NEBULA) shotgun.weapon.active = true;
}

void UpdateWeapon(Player* player) {
    UpdatePhoton(player);
    UpdatePulse(player);
    UpdateShotgun(player);
}

void DrawWeapon() {
    DrawPulseShoot();
    DrawPhotonShoot();
    DrawShotgunShoot();
}

void LoadWeaponTextures(void) {
    texture = LoadTexture("weapons.png");
}

void UnloadWeaponTextures(void) {
    UnloadTexture(texture);
}