// game_constants.h
#include "weapons.h" // Para saber quantas armas implementadas existem

#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

// Tamanho da tela
#define SCREEN_WIDTH 640    // Largura
#define SCREEN_HEIGHT 960  // Altura

// Armas
#define NUMBER_OF_WEAPONS 1 // LEMBRAR DE ATUALIZAR QUANDO TIVER ARMA NOVA

// Waves
#define FIRST_WAVE 0
#define SECOND_WAVE 1
#define THIRD_WAVE 2
#define VICTORY 3

// Wave Threshold
#define FIRST_WAVE_THRESHOLD 10
#define SECOND_WAVE_THRESHOLD 20
#define THIRD_WAVE_THRESHOLD 50

#endif // GAME_CONSTANTS_H