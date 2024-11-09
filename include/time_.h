// weapons.h

#include "raylib.h" // Importando para utilizar os rectangles.
#include "player.h" // Para definir a posição inicial do tiro

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
    float cooldown_time_ms;
    float charge_time_ms;
    Rectangle shoot_source;
    Vector2 shoot_speed;
    Color shoot_color;
    int max_active_shoots;
    struct ActiveShoot shoot[50];
} Weapon;

// WEAPON

void InitWeapons(struct Weapon weapons[], struct Player player) {
    InitPhoton(&weapons[0]);
}

void InitPhoton(struct Weapon *weapon) {
    weapon->id = 0;
    weapon->active = true;
    weapon->number_of_shoots = 50;
    weapon->cooldown_time_ms = 1.0/3.0;
    weapon->charge_time_ms = 0;
    weapon->shoot_source = (Rectangle){ 0, 8, 8, 8 };
    weapon->shoot_speed = (Vector2){0, 1};
    weapon->shoot_color = RED;
    weapon->max_active_shoots = 50;
    for (int i = 0; i < 50; ++i) weapon->shoot[i].active = false;
}

void InitPhotonShoot(struct ActiveShoot *shoot, struct Player player) {
    shoot->active = true;
    shoot->rec.x = (player.rec.x + (player.rec.width / 2) - 3);
    shoot->rec.y = (player.rec.y - 8);
}

void Update


void UpdatePhotonShootPosition(struct Weapon *weapon, struct Enemy enemy[], int active_enemies, int num_shoots, int screen_width, int screen_height) {
    for (int i = 0; i < num_shoots; i++)
    {
        if (!shoot[i].active) continue;

        if (shoot[i].rec.y < -10)
        {
            shoot[i].active = false;
            continue;
        }

        // Movement
        shoot[i].rec.y -= shoot[i].speed.y;

        // Collision with enemy
        for (int j = 0; j < activeEnemies; j++)
        {
            if (enemy[j].active)
            {
                if (CheckCollisionRecs(shoot[i].rec, enemy[j].rec))
                {
                    shoot[i].active = false;
                    enemy[j].rec.x = GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH + 1000);
                    enemy[j].rec.y = GetRandomValue(0, SCREEN_HEIGHT - enemy[j].rec.height);
                    shootRate = 0;
                    enemiesKill++;
                    score += 100;
                }
            }
        }

    }
}


#endif // WEAPONS_H