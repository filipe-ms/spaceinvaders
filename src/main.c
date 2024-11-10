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
#include "game_constants.h"

#include "player.h"
#include "enemies.h"
#include "weapons.h"
#include "power_ups.h"
#include "game_elements.h"

#include "menu_screen.h"
#include "select_ship.h"

//--------------------------------------------------------------
//
//                      VARIÁVEIS GLOBAIS
// 
//--------------------------------------------------------------

// GAME STATE
static GameScreen game_screen = START;
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
    SetTargetFPS(144);
    InitTextures();         // Inicializa o diretório de recursos/assets e as texturas
    InitMenu();

    while (game_screen != EXIT)
    {
        if (WindowShouldClose()) game_screen = EXIT;

        switch (game_screen) {
        case START:
            UpdateMenu(&game_screen);
            DrawMenu();
            break;

        case SELECT_TRANSITION:
            if (MenuTransition()) {
                game_screen = SELECT_SHIP;
                SetTransitionFalse();
                InitSelectMenu();
            }
            break;

        case SELECT_SHIP:
            UpdateSelectMenu(&game_screen);
            DrawSelectMenu();
            break;

        case TUTORIAL_TRANSITION:
            if (SelectMenuTransition()) {
                game_screen = GAME;
                SetSelectTransitionFalse();
                InitGame(); // Inicializa variáveis de jogo
            }
            break;

        case TUTORIAL:

            break;

        case GAME:
            GameLoop();     // Loop de jogo
            break;

        case WINNER:
            break;

        case GAME_OVER:
            break;

        case ENTER_NAME:
            break;

        case RANKING:
            break;

        default:
            UnloadGame();
            CloseWindow();
        }


    }
    
    UnloadGame();           // Free
    CloseWindow();          // Fecha a janela

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
    victory = false;
    smooth = false;
    wave = FIRST;
    activeEnemies = FIRST_WAVE;
    enemiesKill = 0;
    score = 0;
    alpha = 0;
    
    InitShootRatePowerUp(&shootRatePower);  // Inicialização do item power-up de shootRate
    InitPlayer(&player);                    // Initialize player
    InitEnemies(enemy);                     // Initialize enemies
    InitWeapon(weapon, player);             // Initialize weapons
    InitBackground(&background);            // Initialize Background
}

// Update game (one frame)
void UpdateGame(void)
{
    if (game_screen == GAME)
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

            UpdateDrawPlayer(&player);
            UpdatePowerUp(&shootRatePower, weapon, player);                          // Verificar colisão entre o jogador e o item power-up de shootRate
            MovePlayer(&player, GetFrameTime());                                     // Player movement
            UpdateEnemies(enemy, activeEnemies);                                     // Enemy behavior
            
            WallBehavior(&player);                                                   // Colisão com uma parede
            PlayerShoot(weapon, player, enemy, activeEnemies, &enemiesKill, &score); // Shoot
            UpdateBackground(&background);

            if (CheckEnemyCollision(player, enemy, activeEnemies)) game_screen = GAME_OVER;
        }
    } else {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            game_screen = GAME;
        }
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    if (game_screen == GAME)
    {
        DrawBackground(&background);
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
    
    LoadMenuBackgroundTexture();
    LoadSelectMenuTextures();

    LoadPlayerTextures(&player);
    LoadWeaponTextures(weapon);
    LoadEnemyTextures();
    LoadBackgroundTexture(&background);
    
}


// Unload game variables
void UnloadGame(void)
{
    UnloadPlayerTextures(&player);
    UnloadWeaponTextures(weapon);
    
    UnloadEnemyTextures();
    UnloadBackgroundTexture(&background);
    
    UnloadSelectMenuTextures();
    UnloadMenuBackgroundTexture();
}

void GameLoop(void) {
    UpdateGame();
    DrawGame();
}



//--------------------------------------------------------------
//
//                         WAVES
// 
//--------------------------------------------------------------

void FirstWave() {
    if (!smooth)
    {
        alpha += 0.02f * GetFrameTime();

        if (alpha >= 1.0f) smooth = true;
    }

    if (smooth) alpha -= 0.02f * GetFrameTime();

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
        alpha += 0.02f * GetFrameTime();

        if (alpha >= 1.0f) smooth = true;
    }

    if (smooth) alpha -= 0.02f * GetFrameTime();

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
        alpha += 0.02f * GetFrameTime();

        if (alpha >= 1.0f) smooth = true;
    }

    if (smooth) alpha -= 0.02f * GetFrameTime();

    if (enemiesKill == activeEnemies) victory = true;
}