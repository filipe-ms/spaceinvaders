// power_ups.c

#include "power_ups.h"
#include "game_constants.h"

void InitShootRatePowerUp(struct PowerUpShootRate* power) {
    power->rec.width = 20;  // Define a largura do item
    power->rec.height = 20; // Define a altura do item
    power->rec.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(power->rec.width));  // Posição aleatória x
    power->rec.y = (float)GetRandomValue(0, SCREEN_HEIGHT - (int)(power->rec.height)); // Posição aleatória y
    power->active = true;   // Item começa ativo
    power->color = RED;     // Define a cor do item como vermelha
}

void SpawnShootRatePowerUp(struct PowerUpShootRate* power) {
    if (!power->active) {
        // Ativa o item e define uma nova posição aleatória quando a segunda onda começa
        power->rec.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(power->rec.width));
        power->rec.y = (float)GetRandomValue(0, SCREEN_HEIGHT - (int)(power->rec.height));
        power->active = true;
    }
}

void DrawPowerUps(struct PowerUpShootRate power) {
    if (power.active) {
        DrawRectangleRec(power.rec, power.color);
    }
}

void UpdatePowerUp(struct PowerUpShootRate* power, struct Weapon* weapon, struct Player player) {
    if (power->active && CheckCollisionRecs(player.position, power->rec)) {
        // Diminui o intervalo de frame do shootRate em 20%
        weapon[0].charge_time_modifier += 0.2f;

        // Desativa o item após coleta
        power->active = false;
    }
}
