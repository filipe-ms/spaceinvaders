// game_constants.h

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

// Waves
typedef enum {
    FIRST = 0,
    SECOND = 1,
    THIRD = 2
} EnemyWave;

// Screens
typedef enum {
    START = 0,
    SELECT_TRANSITION,
    SELECT_SHIP,
    TUTORIAL_TRANSITION,
    TUTORIAL,
    GAME,
    WINNER,
    GAME_OVER,
    ENTER_NAME,
    RANKING,
    EXIT
} GameScreen;


#endif // GAME_CONSTANTS_H