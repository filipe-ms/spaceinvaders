// weapons.c

#include "weapons.h"
#include "game_constants.h"
#include "draw_object.h"
#include "math.h"

Texture texture;

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
    pulse.weapon.pivot = (Vector2){ 20, 9 };
    pulse.weapon.color = WHITE;

    pulse.weapon.damage = 1.0f;

    pulse.weapon.cooldown_time_s = 1.0 / 2.0f;
    pulse.weapon.cooldown_charge_s = 0;
    pulse.weapon.charge_time_modifier = 1;

    pulse.weapon.max_active_shoots = 50;
	
    pulse.speed_1 = (Vector2){ -25.88f * speed_factor, -100 * speed_factor };
    pulse.speed_2 = (Vector2){ 25.88f * speed_factor, -100 * speed_factor };
    pulse.speed_3 = (Vector2){ 0, -100 * speed_factor };

    pulse.rotation_1 = -15;
    pulse.rotation_2 = 15;

    pulse.weapon_cycle = 0;

	pulse.weapon.speed = (Vector2){ 0, 0 }; // Unused

    for (int i = 0; i < 50; i++) {
        
		pulse.pulse_shoot->shoot.active = false;
		pulse.pulse_shoot->shoot.damage = pulse.weapon.damage;
		
        pulse.pulse_shoot[i].shoot.draw_position.height = 72;
        pulse.pulse_shoot[i].shoot.draw_position.width = 72;

        pulse.pulse_shoot[i].shoot.position.width = 36;
        pulse.pulse_shoot[i].shoot.position.height = 32;
    }
}

InitPulseShoot(Player *player) {

    for (int i = 0; i < 50; i++) {
		if (!pulse.pulse_shoot[i].shoot.active) {

            pulse.pulse_shoot[i].shoot.active = true;

            if (pulse.weapon_cycle == 0) {
                pulse.pulse_shoot[i].shoot.position.x = player->position.x + 6;
                pulse.pulse_shoot[i].shoot.position.y = player->position.y;

                pulse.pulse_shoot[i].shoot.draw_position.x = player->position.x + 16;
                pulse.pulse_shoot[i].shoot.draw_position.y = player->position.y - 16;
                pulse.pulse_shoot[i].shoot_cycle = pulse.weapon_cycle;
                pulse.weapon_cycle++;
            }

            else if (pulse.weapon_cycle == 1) {
                pulse.pulse_shoot[i].shoot.position.x = player->position.x + 6;
                pulse.pulse_shoot[i].shoot.position.y = player->position.y;

                pulse.pulse_shoot[i].shoot.draw_position.x = player->position.x + 32;
                pulse.pulse_shoot[i].shoot.draw_position.y = player->position.y - 16;

                pulse.pulse_shoot[i].shoot_cycle = pulse.weapon_cycle;
                pulse.weapon_cycle++;
			}

            else {
                pulse.pulse_shoot[i].shoot.position.x = player->position.x + 6;
                pulse.pulse_shoot[i].shoot.position.y = player->position.y;

                pulse.pulse_shoot[i].shoot.draw_position.x = player->position.x + 26;
                pulse.pulse_shoot[i].shoot.draw_position.y = player->position.y - 18;

                pulse.pulse_shoot[i].shoot_cycle = pulse.weapon_cycle;
                pulse.weapon_cycle = 0;
            }

			break;
		}
    }
}

void UpdatePulseShoot() {
    for (int i = 0; i < 50; i++) {
        if (!pulse.pulse_shoot[i].shoot.active) continue;

        if (pulse.pulse_shoot[i].shoot_cycle == 0) {
            pulse.pulse_shoot[i].shoot.position.x += pulse.speed_1.x * GetFrameTime();
            pulse.pulse_shoot[i].shoot.position.y += pulse.speed_1.y * GetFrameTime();

            pulse.pulse_shoot[i].shoot.draw_position.x += pulse.speed_1.x * GetFrameTime();
            pulse.pulse_shoot[i].shoot.draw_position.y += pulse.speed_1.y * GetFrameTime();

            if (pulse.pulse_shoot[i].shoot.position.y < -80) {
                pulse.pulse_shoot[i].shoot.active = false;
            }

        } else if (pulse.pulse_shoot[i].shoot_cycle == 1) {
            pulse.pulse_shoot[i].shoot.position.x += pulse.speed_2.x * GetFrameTime();
            pulse.pulse_shoot[i].shoot.position.y += pulse.speed_2.y * GetFrameTime();

            pulse.pulse_shoot[i].shoot.draw_position.x += pulse.speed_2.x * GetFrameTime();
            pulse.pulse_shoot[i].shoot.draw_position.y += pulse.speed_2.y * GetFrameTime();

            if (pulse.pulse_shoot[i].shoot.position.y < -80) {
                pulse.pulse_shoot[i].shoot.active = false;
            }

        } else {
            pulse.pulse_shoot[i].shoot.position.x += pulse.speed_3.x * GetFrameTime();
            pulse.pulse_shoot[i].shoot.position.y += pulse.speed_3.y * GetFrameTime();

            pulse.pulse_shoot[i].shoot.draw_position.x += pulse.speed_3.x * GetFrameTime();
            pulse.pulse_shoot[i].shoot.draw_position.y += pulse.speed_3.y * GetFrameTime();

            if (pulse.pulse_shoot[i].shoot.position.y < -80) {
                pulse.pulse_shoot[i].shoot.active = false;
            }
        }
    }
}

void UpdatePulse(Player *player) {
	if (!pulse.weapon.active) return;

    UpdatePulseShoot();

    pulse.weapon.cooldown_charge_s += pulse.weapon.charge_time_modifier * GetFrameTime();

    if (pulse.weapon.cooldown_charge_s >= pulse.weapon.cooldown_time_s) {
		InitPulseShoot(player);
        pulse.weapon.cooldown_charge_s -= pulse.weapon.cooldown_time_s;
    }
}

void DrawPulseShoot() {
    for (int i = 0; i < 50; i++) {
        if (pulse.pulse_shoot[i].shoot.active) {
            if (pulse.pulse_shoot[i].shoot_cycle == 0) {
                DrawTexturePro(texture, pulse.weapon.source, pulse.pulse_shoot[i].shoot.draw_position, pulse.weapon.pivot, pulse.rotation_1, WHITE);
            }
            else if (pulse.pulse_shoot[i].shoot_cycle == 1) {
                DrawTexturePro(texture, pulse.weapon.source, pulse.pulse_shoot[i].shoot.draw_position, pulse.weapon.pivot, pulse.rotation_2, WHITE);
            }
            else {
                DrawTexturePro(texture, pulse.weapon.source, pulse.pulse_shoot[i].shoot.draw_position, pulse.weapon.pivot, 0, WHITE);
            }
        }
    }
}

Shoot* GetPulseShoot(int index) {
    return &pulse.pulse_shoot[index].shoot;
}

bool CheckPulseCollision(int index, Enemy *enemy) {
    if (!pulse.pulse_shoot[index].shoot.active) return false;;
        
    if (CheckCollisionRecs(pulse.pulse_shoot[index].shoot.position, enemy->position))
    {
        return true;
    }
	return false;
}

//--------------------------------------------------------------

Photon photon;

void InitPhoton() {

    photon.weapon.id = PHOTON;
    photon.weapon.active = false;

    photon.weapon.source = (Rectangle){ 0, 8, 8, 8 };
    photon.weapon.pivot = (Vector2){ 4, 4 };

    photon.weapon.cooldown_time_s = (float)(1.0f / 3.0f);
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
    }
}

void InitPhotonShoot(Player *player) {
    for (int i = 0; i < photon.weapon.max_active_shoots; i++) {
		if (photon.shoot[i].active) continue;

        photon.shoot[i].active = true;
        photon.shoot[i].position.x = (player->position.x) + 6;
        photon.shoot[i].position.y = (player->position.y - 4);

        photon.shoot[i].draw_position.x = (player->position.x) + 27;
        photon.shoot[i].draw_position.y = (player->position.y - 20);
        break;
    }
}


void UpdatePhotonCooldownAndShoot(Player* player) {
	if (!photon.weapon.active) return;

	photon.weapon.cooldown_charge_s += photon.weapon.charge_time_modifier * GetFrameTime();

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
        photon.shoot[i].position.x += photon.weapon.speed.x * GetFrameTime();
        photon.shoot[i].draw_position.y -= photon.weapon.speed.y * GetFrameTime();
        photon.shoot[i].draw_position.x += photon.weapon.speed.x * GetFrameTime();
    }
}

void DrawPhotonShoot() {
    for (int i = 0; i < NUMBER_OF_WEAPONS; i++) {
        if (photon.shoot[i].active) {
            DrawTexturePro(texture, photon.weapon.source, photon.shoot[i].draw_position, photon.weapon.pivot, 0, WHITE);
        }
    }
}

void UpdatePhoton(Player* player) {
    UpdatePhotonShootPosition();
	UpdatePhotonCooldownAndShoot(player);
}

//--------------------------------------------------------------

void InitAllWeapons() {
    InitPulse();
    InitPhoton();
}

void InitWeapon(Player* player) {
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
    DrawPhotonShoot();
    DrawPulseShoot();
}

void LoadWeaponTextures(void) {
    texture = LoadTexture("weapons.png");
}

void UnloadWeaponTextures(void) {
    UnloadTexture(texture);
}




