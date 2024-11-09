// weapons.h

#include "raylib.h" // Importando para utilizar os rectangles.
#include "player.h" // Para definir a posição inicial do tiro
#include "time_management.h" // Para eventos que utilizam tempo

#ifndef WEAPONS_H
#define WEAPONS_H

#define PHOTON 0
#define NUMBER_OF_WEAPONS 1
#define MAX_ACTIVE_SHOOTS 50

typedef struct ActiveShoot {
    Rectangle rec;
    bool active;
} ActiveShoot;

typedef struct Weapon {
    int id;
    bool active;
    float number_of_shoots;
    float cooldown_time_s;
    float charge_time_s;
    float charge_time_modifier;
    Rectangle shoot_source;
    Vector2 shoot_speed;
    Color shoot_color;
    int max_active_shoots;
    struct ActiveShoot shoot[50];
} Weapon;

Texture weapon_texture;
Vector2 weapon_pivot = { 4, 4 };

void LoadWeaponTextures();
void UnloadWeaponTextures();
void InitWeapon(struct Weapon* weapons, struct Player player);
void InitWeaponShoot(struct ActiveShoot* shoot, struct Player player);
void PlayerShoot(void);
void CheckWeaponCooldownAndShoot(struct Weapon* weapon, struct Player player);
void UpdateShootPosition(struct Weapon* weapon, struct Enemy enemy[], int active_enemies, int* enemy_kill, int* score, int screen_width, int screen_height);
void DrawWeaponShoot(struct Weapon weapon);

void InitPhoton(struct Weapon* weapon);



void InitWeaponShoot(struct ActiveShoot* shoot, struct Player player) {
    shoot->active = true;
    shoot->rec.x = (player.rec.x + (player.rec.width / 2) - 3);
    shoot->rec.y = (player.rec.y - 8);
}

void PlayerShoot(struct Weapon *weapon, struct Player player, struct Enemy *enemy, int activeEnemies, int *enemiesKill, int *score, int screen_width, int screen_height) {
    CheckWeaponCooldownAndShoot(&weapon[0], player);
    UpdateShootPosition(&weapon[0], enemy, activeEnemies, enemiesKill, score, screen_width, screen_height);
}

void CheckWeaponCooldownAndShoot(struct Weapon* weapon, struct Player player) {
    weapon->charge_time_s += GetUpdatedDelta() * weapon->charge_time_modifier;
    if (weapon->charge_time_s >= weapon->cooldown_time_s) {
        for (int i = 0; i < weapon->max_active_shoots; i++) {
            if (!weapon->shoot[i].active) {
                InitWeaponShoot(&weapon->shoot[i], player);
                break;
            }
        }
        weapon->charge_time_s -= weapon->cooldown_time_s;
    }
}



void UpdateShootPosition(struct Weapon* weapon, struct Enemy enemy[], int active_enemies, int* enemy_kill, int* score, int screen_width, int screen_height) {
    for (int i = 0; i < weapon->max_active_shoots; i++)
    {
        if (!weapon->shoot[i].active) continue;

        if (weapon->shoot[i].rec.y < -10)
        {
            weapon->shoot[i].active = false;
            continue;
        }

        // Movement
        weapon->shoot[i].rec.y -= weapon->shoot_speed.y * GetUpdatedDelta();

        // Collision with enemy
        for (int j = 0; j < active_enemies; j++)
        {
            if (enemy[j].active)
            {
                if (CheckCollisionRecs(weapon->shoot[i].rec, enemy[j].rec))
                {
                    weapon->shoot[i].active = false;
                    enemy[j].rec.x = GetRandomValue(screen_width, screen_width + 1000);
                    enemy[j].rec.y = GetRandomValue(0, screen_height - enemy[j].rec.height);
                    *enemy_kill += 1;
                    *score += 100;
                }
            }
        }

    }
}

void DrawWeaponShoot(struct Weapon weapon) {
    for (int i = 0; i < weapon.max_active_shoots; i++)
    {
        if (weapon.shoot[i].active) {
            Rectangle drawn_shoot = weapon.shoot[i].rec;
            drawn_shoot.y -= 5;
            drawn_shoot.width = 16;
            drawn_shoot.height = 16;
            DrawTexturePro(weapon_texture, weapon.shoot_source, drawn_shoot, weapon_pivot, 0, WHITE);
        }
    }
}

void LoadWeaponTextures() {
    weapon_texture = LoadTexture("weapons.png");
}

void UnloadWeaponTextures() {
    UnloadTexture(weapon_texture);
}


void InitWeapon(struct Weapon* weapons, struct Player player) {
    InitPhoton(&weapons[0]);
}

void InitPhoton(struct Weapon *weapon) {
    weapon->id = 0;
    weapon->active = true;
    weapon->number_of_shoots = 50;
    weapon->cooldown_time_s = 1.0/3.0f;
    weapon->charge_time_s = 0;
    weapon->charge_time_modifier = 1;
    weapon->shoot_source = (Rectangle){ 0, 8, 8, 8 };
    weapon->shoot_speed = (Vector2){0, 720};
    weapon->shoot_color = RED;
    weapon->max_active_shoots = 50;
    for (int i = 0; i < 50; ++i) weapon->shoot[i].active = false;
}




#endif // WEAPONS_H