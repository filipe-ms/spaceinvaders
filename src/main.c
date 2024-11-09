/*******************************************************************************************
*
*   raylib - classic game: space invaders
*
*   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

//--------------------------------------------------------------
//
//                         IMPORTS
// 
//--------------------------------------------------------------

// Raylib
#include "raylib.h"
#include "resource_dir.h"

// Outras libs
#include "math.h"

// Nossos próprios includes
#include "player.h"
#include "enemies.h"
#include "weapons.h"
#include "power_ups.h"
#include "game_behavior.h"
#include "time_management.h"
#include "game_elements.h"

//--------------------------------------------------------------
//
//                         DEFINES
// 
//--------------------------------------------------------------

// Tamanho da tela
#define SCREEN_WIDTH 800    // Largura
#define SCREEN_HEIGHT 1200  // Altura

// Elementos de tela
#define NUM_MAX_ENEMIES 50  // Número máximo de inimigos na tela

// Timers
#define FIRST_WAVE 10
#define SECOND_WAVE 20
#define THIRD_WAVE 50

// Waves
typedef enum { 
    FIRST = 0, 
    SECOND = 1, 
    THIRD = 2
} EnemyWave;



//--------------------------------------------------------------
//
//                      VARIÁVEIS GLOBAIS
// 
//--------------------------------------------------------------

// GAME STATE
static bool game_over = false;
static bool pause = false;
static bool pause_flag = false;
static bool victory = false;
static int score = 0;

// ENTITIES
static Player player = { 0 };
static Weapon weapon[NUMBER_OF_WEAPONS];
static Enemy enemy[NUM_MAX_ENEMIES] = { 0 };

// BACKGROUND
static Background background;

// WAVE
static EnemyWave wave = { 0 };
static float alpha = 0.0f;
static bool smooth = false;

// COUNTS
static int activeEnemies = 0;
static int enemiesKill = 0;

// POWERS
static PowerUpShootRate shootRatePower;


//--------------------------------------------------------------
//
//                         FUNÇÕES (declaração)
// 
//--------------------------------------------------------------

static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void GameLoop(void);         // Update and Draw (one frame)

// TEXTURAS
void InitTextures(void);

// WAVES
static void FirstWave(void);
static void SecondWave(void);
static void ThirdWave(void);

//--------------------------------------------------------------
//
//                           MAIN
// 
//--------------------------------------------------------------
int main(void)
{
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders"); // Inicializa a janela do jogo
    InitTextures();         // Inicializa o diretório de recursos/assets e as texturas
    InitGame();             // Inicializa variáveis de jogo
    GameLoop();             // Loop de jogo
    UnloadGame();           // Encerramento
    CloseWindow();          // Close window and OpenGL context

    return 0;
}

//--------------------------------------------------------------
//
//                         FUNÇÕES (descrição)
// 
//--------------------------------------------------------------

// Initialize game variables
void InitGame(void) {

    // Initialize game variables
    pause = false;
    game_over = false;
    victory = false;
    smooth = false;
    wave = FIRST;
    activeEnemies = FIRST_WAVE;
    enemiesKill = 0;
    score = 0;
    alpha = 0;
    
    InitShootRatePowerUp(&shootRatePower, SCREEN_WIDTH, SCREEN_HEIGHT); // Inicialização do item power-up de shootRate
    InitPlayer(&player, SCREEN_WIDTH, SCREEN_HEIGHT);                   // Initialize player
    InitEnemies(enemy, NUM_MAX_ENEMIES, SCREEN_WIDTH, SCREEN_HEIGHT);   // Initialize enemies
    InitWeapon(weapon, player);                                         // Initialize weapons
    InitBackground(&background);                                        // Initialize Background
}

// Update game (one frame)
void UpdateGame(void)
{
    if (!game_over)
    {
        if (IsKeyPressed('P') && !pause_flag) {
            pause = !pause;
            pause_flag = true;
        }
        if (IsKeyReleased('P')) {
            pause_flag = false;
        }

        if (!pause)
        {
            if(wave == FIRST)
                FirstWave();
            else if(wave == SECOND)
                SecondWave();
            else if (wave == THIRD)
                ThirdWave();

            UpdatePowerUp(&shootRatePower, weapon, player);                                                                 // Verificar colisão entre o jogador e o item power-up de shootRate
            MovePlayer(&player, GetUpdatedDelta());                                                                 // Player movement
            UpdateEnemies(enemy, activeEnemies, SCREEN_WIDTH, SCREEN_HEIGHT);                                       // Enemy behavior
            CheckEnemyCollision(&player, enemy, activeEnemies, &game_over);                                         // Colisão com um inimigo
            WallBehavior(&player, SCREEN_WIDTH, SCREEN_HEIGHT);                                                     // Colisão com uma parede
            PlayerShoot(weapon, player, enemy, activeEnemies, &enemiesKill, &score, SCREEN_WIDTH, SCREEN_HEIGHT);    // Shoot
        }
    } else {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            game_over = false;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (!game_over)
    {
        
        UpdateAndDrawBackground(&background);
        DrawPowerUps(shootRatePower);
        DrawPlayer(&player);
        DrawEnemies(enemy, activeEnemies);
        DrawWeaponShoot(weapon[0]);

        if (wave == FIRST) DrawText("FIRST WAVE", SCREEN_WIDTH / 2 - MeasureText("FIRST WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, Fade(WHITE, alpha));
        else if (wave == SECOND) DrawText("SECOND WAVE", SCREEN_WIDTH / 2 - MeasureText("SECOND WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, Fade(WHITE, alpha));
        else if (wave == THIRD) DrawText("THIRD WAVE", SCREEN_WIDTH / 2 - MeasureText("THIRD WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, Fade(WHITE, alpha));

        DrawText(TextFormat("%04i", score), 20, 20, 40, GRAY);

        if (victory) DrawText("YOU WIN", SCREEN_WIDTH / 2 - MeasureText("YOU WIN", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, WHITE);

        if (pause) DrawText("GAME PAUSED", SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GRAY);
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    
    EndDrawing();
}


// Inicializa as texturas no jogo
void InitTextures() {
    SearchAndSetResourceDir("resources");

    LoadWeaponTextures();
    LoadPlayerTextures();
    LoadEnemyTextures();
    LoadBackgroundTexture(&background);
}


// Unload game variables
void UnloadGame(void)
{
    UnloadWeaponTextures();
    UnloadPlayerTextures();
    UnloadEnemyTextures();
    UnloadBackgroundTexture(&background);
}

void GameLoop(void) {

    InitUpdateStart();
  
    while (!WindowShouldClose()) 
    {
        do {
            UpdateGame();
            UpdateTime();
        } while (!IsItTimeToDraw());
        GameLoopUpdate();

        DrawGame(); 
    } 
}



//--------------------------------------------------------------
//
//                         WAVES
// 
//--------------------------------------------------------------

void FirstWave() {
    if (!smooth)
    {
        alpha += 0.02f;

        if (alpha >= 1.0f) smooth = true;
    }

    if (smooth) alpha -= 0.02f;

    if (enemiesKill == activeEnemies)
    {
        enemiesKill = 0;

        for (int i = 0; i < activeEnemies; i++)
        {
            if (!enemy[i].active) enemy[i].active = true;
        }

        activeEnemies = SECOND_WAVE;
        wave = SECOND;
        smooth = false;
        alpha = 0.0f;
    }
}

void SecondWave() {

    SpawnShootRatePowerUp(&shootRatePower, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (!smooth)
    {
        alpha += 0.02f;

        if (alpha >= 1.0f) smooth = true;
    }

    if (smooth) alpha -= 0.02f;

    if (enemiesKill == activeEnemies)
    {
        enemiesKill = 0;

        for (int i = 0; i < activeEnemies; i++)
        {
            if (!enemy[i].active) enemy[i].active = true;
        }

        activeEnemies = THIRD_WAVE;
        wave = THIRD;
        smooth = false;
        alpha = 0.0f;
    }
}

void ThirdWave() {
    if (!smooth)
    {
        alpha += 0.02f;

        if (alpha >= 1.0f) smooth = true;
    }

    if (smooth) alpha -= 0.02f;

    if (enemiesKill == activeEnemies) victory = true;
}