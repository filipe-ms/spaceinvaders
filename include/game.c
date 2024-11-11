#include "game.h"
#include "enemy.h"
#include "commons.h"
#include "weapons.h"

#include "power_ups.h"
#include "game_constants.h"
#include "scene_manager.h"

#include "math.h"

// GAME STATE
static bool pause = false;
static bool pause_flag = false;
static bool victory = false;
static int score = 0;
static Player player = { 0 };
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

static Weapon weapon[NUMBER_OF_WEAPONS];


void InitGame(int ship_id) {

    // Initialize game variables
    pause = false;
    victory = false;
    smooth = false;
    wave = FIRST;
    activeEnemies = FIRST_WAVE;
    enemiesKill = 0;
    score = 0;
    alpha = 0;
    
    InitPlayer(&player, ship_id);
    InitShootRatePowerUp(&shootRatePower);  // Inicialização do item power-up de shootRate
    InitEnemies(enemy);                     // Initialize enemies
    InitWeapon(&weapon, player);             // Initialize weapons
    

    background.position_y = -1200;
    background.color = (Color){ 255, 255, 255, 170 };
    background.alpha = 0;
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

    SpawnShootRatePowerUp(&shootRatePower);

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



//--------------------------------------------------------------
//
//                         UPDATE
// 
//--------------------------------------------------------------

void UpdateBackground(Background* background) {
    if (background->alpha < 0.7) background->alpha += 0.2f * GetFrameTime();
    background->position_y = fmod(background->position_y + 75 * GetFrameTime(), 2400);
}


void UpdateGame(void)
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
        if (wave == FIRST)
            FirstWave();
        else if (wave == SECOND)
            SecondWave();
        else if (wave == THIRD)
            ThirdWave();

        UpdatePlayer(&player);
        UpdatePowerUp(&shootRatePower, weapon, player);                          // Verificar colisão entre o jogador e o item power-up de shootRate
        UpdateEnemies(enemy, activeEnemies);                                     // Enemy behavior
        PlayerShoot(weapon, player, enemy, activeEnemies, &enemiesKill, &score); // Shoot
        UpdateBackground(&background);

        if (CheckEnemyCollision(player, enemy, activeEnemies)) ChangeScene(GAME_OVER);
    }
}

//--------------------------------------------------------------
//
//                         DRAW
// 
//--------------------------------------------------------------

void DrawBackground() {
    DrawTexture(background.texture, background.position_x, background.position_y, Fade(background.color, background.alpha));
    DrawTexture(background.texture, (int)(background.position_x), (int)(background.position_y) - 2400, Fade(background.color, background.alpha));
}

void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawBackground();
    DrawPowerUps(shootRatePower);
    DrawWeaponShoot(weapon[0]);
    DrawPlayer(player);
    DrawEnemies(enemy, activeEnemies);

    if (wave == FIRST) DrawText("FIRST WAVE", SCREEN_WIDTH / 2 - MeasureText("FIRST WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, Fade(WHITE, alpha));
    else if (wave == SECOND) DrawText("SECOND WAVE", SCREEN_WIDTH / 2 - MeasureText("SECOND WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, Fade(WHITE, alpha));
    else if (wave == THIRD) DrawText("THIRD WAVE", SCREEN_WIDTH / 2 - MeasureText("THIRD WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, Fade(WHITE, alpha));

    DrawText(TextFormat("%04i", score), 20, 20, 40, GRAY);

    if (victory) DrawText("YOU WIN", SCREEN_WIDTH / 2 - MeasureText("YOU WIN", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, WHITE);

    if (pause) DrawText("GAME PAUSED", SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GRAY);

    EndDrawing();
}



//--------------------------------------------------------------
//
//                     LOAD | UNLOAD
// 
//--------------------------------------------------------------

void LoadGameTextures(void) {
    background.texture = LoadTexture("purplebg.png");

    LoadWeaponTextures(weapon);
}

void UnloadGameTextures(void) {
    UnloadTexture(background.texture);

    UnloadWeaponTextures(weapon);
}