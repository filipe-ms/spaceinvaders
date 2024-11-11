// game_constants.h
#include "weapons.h" // Para saber quantas armas implementadas existem

#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

// Tamanho da tela
#define SCREEN_WIDTH 800    // Largura
#define SCREEN_HEIGHT 1200  // Altura

// Elementos de tela
#define NUM_MAX_ENEMIES 50  // Número máximo de inimigos na tela

// Wave Threshold
#define FIRST_WAVE 10
#define SECOND_WAVE 20
#define THIRD_WAVE 50

// Armas
#define NUMBER_OF_WEAPONS 1 // LEMBRAR DE ATUALIZAR QUANDO TIVER ARMA NOVA

// Waves
typedef enum {
    FIRST = 0,
    SECOND = 1,
    THIRD = 2
} EnemyWave;


#endif // GAME_CONSTANTS_H