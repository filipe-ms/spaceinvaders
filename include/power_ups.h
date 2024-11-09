// power_ups.h

#include "raylib.h" // Importando para utilizar os rectangles.
#include "player.h"

#ifndef POWER_UPS_H
#define POWER_UPS_H

// Shoot Rate Power Up
typedef struct PowerUpShootRate {
    Rectangle rec;  // Posição e tamanho do item
    bool active;    // Estado ativo/inativo do item
    Color color;    // Cor do item
} PowerUpShootRate; // Declaração da variável global do item

// Init no power up de ShootRate

void InitShootRatePowerUp(struct PowerUpShootRate *power, int screen_width, int screen_height) {
    power->rec.width = 20;  // Define a largura do item
    power->rec.height = 20; // Define a altura do item
    power->rec.x = GetRandomValue(0, screen_width - power->rec.width);  // Posição aleatória x
    power->rec.y = GetRandomValue(0, screen_height - power->rec.height); // Posição aleatória y
    power->active = true;   // Item começa ativo
    power->color = RED;     // Define a cor do item como vermelha
}

// Elaborar melhor essa função depois, utilizando tempo como parâmetro.
void SpawnShootRatePowerUp(struct PowerUpShootRate *power, int screen_width, int screen_height) {
    if (!power->active) {
        // Ativa o item e define uma nova posição aleatória quando a segunda onda começa
        power->rec.x = GetRandomValue(0, screen_width - power->rec.width);
        power->rec.y = GetRandomValue(0, screen_height - power->rec.height);
        power->active = true;
    }
}

void DrawPowerUps(struct PowerUpShootRate power) {
    if (power.active) {
        DrawRectangleRec(power.rec, power.color);
    }
}

void UpdatePowerUp(struct PowerUpShootRate *power, struct Weapon *weapon, struct Player player) {
    if (power->active && CheckCollisionRecs(player.rec, power->rec)) {
        // Diminui o intervalo de frame do shootRate em 20%
        weapon[0].charge_time_modifier += 0.2;

        // Desativa o item após coleta
        power->active = false;
    }
}

#endif // POWER_UPS_H