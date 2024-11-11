// weapons.c

#include "weapons.h"
#include "game_constants.h"

void LoadWeaponTextures(Weapon *weapon) {
    for(int i=0; i < NUMBER_OF_WEAPONS; i++)
        weapon[i].texture = LoadTexture("weapons.png");
}

void UnloadWeaponTextures(Weapon *weapon) {
    for (int i=0; i < NUMBER_OF_WEAPONS; i++){
        UnloadTexture(weapon[i].texture);
    }
}

void InitWeapon(Weapon* weapons, Player player) {
    InitPhoton(&weapons[0]);
}

void InitPhoton(Weapon* weapon) {

    weapon->id = PHOTON;
    weapon->active = true;

    weapon->source = (Rectangle){ 0, 8, 8, 8 };
    weapon->pivot = (Vector2){ 4, 4 };

    weapon->cooldown_time_s = 1.0 / 3.0f;
    weapon->cooldown_charge_s = 0;
    weapon->charge_time_modifier = 1;

    weapon->max_active_shoots = 50;

    weapon->shoot_speed = (Vector2){ 0, 720 };
    weapon->shoot_color = RED;

    for (int i = 0; i < weapon->max_active_shoots; ++i) {
        weapon->shoot[i].active = false;
    }
}

void InitWeaponShoot(ActiveShoot* shoot, Player player) {
    shoot->active = true;
    shoot->rec.x = (player.position.x + 30);
    shoot->rec.y = (player.position.y - 4);
}

void PlayerShoot(Weapon* weapon, Player player, Enemy* enemy, int activeEnemies, int* enemiesKill, int* score) {
    CheckWeaponCooldownAndShoot(&weapon[0], player);
    UpdateShootPosition(&weapon[0], enemy, activeEnemies, enemiesKill, score);
}

void CheckWeaponCooldownAndShoot(Weapon* weapon, Player player) {
    weapon->cooldown_charge_s += weapon->charge_time_modifier * GetFrameTime();
    if (weapon->cooldown_charge_s >= weapon->cooldown_time_s) {
        for (int i = 0; i < weapon->max_active_shoots; i++) {
            if (!weapon->shoot[i].active) {
                InitWeaponShoot(&weapon->shoot[i], player);
                break;
            }
        }
        weapon->cooldown_charge_s -= weapon->cooldown_time_s;
    }
}

void UpdateShootPosition(Weapon* weapon, Enemy *enemy, int active_enemies, int* enemy_kill, int* score) {
    for (int i = 0; i < weapon->max_active_shoots; i++) {
        if (!weapon->shoot[i].active) continue;

        if (weapon->shoot[i].rec.y < -10) {
            weapon->shoot[i].active = false;
            continue;
        }

        // Movement
        weapon->shoot[i].rec.y -= weapon->shoot_speed.y * GetFrameTime();

        // Collision with enemy
        for (int j = 0; j < active_enemies; j++) {
            if (enemy[j].active) {
                if (CheckCollisionRecs(weapon->shoot[i].rec, enemy[j].rec)) {
                    weapon->shoot[i].active = false;
                    enemy[j].rec.x = (float)GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH + 1000);
                    enemy[j].rec.y = (float)GetRandomValue(0, SCREEN_HEIGHT - enemy[j].rec.height);
                    (*enemy_kill)++;
                    (*score) += 100;
                }
            }
        }
    }
}

void DrawWeaponShoot(Weapon weapon) {
    for (int i = 0; i < weapon.max_active_shoots; i++) {
        if (weapon.shoot[i].active) {
            Rectangle drawn_shoot = weapon.shoot[i].rec;
            drawn_shoot.y -= 5;
            drawn_shoot.width = 16;
            drawn_shoot.height = 16;
            DrawTexturePro(weapon.texture, weapon.source, drawn_shoot, weapon.pivot, 0, WHITE);
        }
    }
}
