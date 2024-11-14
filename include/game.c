#include "game.h"
#include "enemy.h"
#include "common.h"
#include "weapon.h"
#include "xp_bar.h"
#include "power_ups.h"
#include <math.h>
#include "scene_manager.h"

// Waves
#define FIRST_WAVE 0
#define SECOND_WAVE 1
#define THIRD_WAVE 2
#define VICTORY 3

// Wave Threshold
#define FIRST_WAVE_THRESHOLD 10
#define SECOND_WAVE_THRESHOLD 20
#define THIRD_WAVE_THRESHOLD 50

// GAME STATE
static bool pause = false;
static bool pause_flag = false;
static bool victory = false;

static Player player = { 0 };
static Enemy enemy[50] = { 0 };

// BACKGROUND
static Background background;

// WAVE
int active_wave;
bool wave_completed;
float wave_message_alpha;
bool wave_message_alpha_flag;

// WAVE COUNTERS
float wave_3_enemy_cooldown_s = 1;
float wave_3_enemy_cooldown_charge_s = 0;

// COUNTS
int player_score;
int enemies_killed;

// BUFFS AND POWERS
bool level_up_flag = false;

void InitGame(int ship_id) {

    static bool pause = false;
    static bool pause_flag = false;
    static bool victory = false;

    // Special Conditions
    pause = false;
    pause_flag = false;
    victory = false;
    
    // Wave
    active_wave = THIRD_WAVE;
    wave_completed = false;
    wave_message_alpha = 0.0f;
    wave_message_alpha_flag = false;

    // Enemies
    enemies_killed = 0;
    player_score = 0;

    // Buffs
    level_up_flag = false;

    // Other inits
    InitPlayer(&player, ship_id);
    InitEnemies(enemy);                     // Initialize enemies
    InitWeapon(&player);           // Initialize weapons
    InitExpBar();

	// Background
    background.position_y = -1200;
    background.color = (Color){ 255, 255, 255, 170 };
    background.alpha = 0;
}

//--------------------------------------------------------------
//
//                         WAVES
// 
//--------------------------------------------------------------

void UpdateWaveAlpha() {
    if (wave_message_alpha >= 1.0f) {
        wave_message_alpha_flag = true;
    }

    if (!wave_message_alpha_flag && !wave_completed) {
        wave_message_alpha += 0.5f * GetFrameTime();
        if (wave_message_alpha > 1.0f) wave_message_alpha = 1.0f;
    }
    else if (wave_message_alpha_flag || wave_completed) {
        wave_message_alpha -= 0.5f * GetFrameTime();
        if (wave_message_alpha < 0.0f) wave_message_alpha = 0.0f;
    }
}


void FirstWave() {

    // Condition for next wave
    if (wave_completed) {
        active_wave = SECOND_WAVE;
        wave_completed = false;
    }
}

void SecondWave() {

    // Condition for next wave
    if (wave_completed){
        active_wave = THIRD_WAVE;
        wave_completed = false;
    }
}

void ThirdWave() {

    wave_3_enemy_cooldown_charge_s += GetFrameTime();
    if (wave_3_enemy_cooldown_charge_s >= wave_3_enemy_cooldown_s) {
        SpawnEnemies(enemy, 10, 0);
		wave_3_enemy_cooldown_charge_s =- wave_3_enemy_cooldown_s;
    }


    // Condition for next wave
    if (wave_completed) {
        victory = true;
        active_wave = VICTORY;
        wave_completed = false;
    }
}

void UpdateWave() {
	if (active_wave == FIRST_WAVE) FirstWave();
	else if (active_wave == SECOND_WAVE) SecondWave();
	else if (active_wave == THIRD_WAVE) ThirdWave();
}

//--------------------------------------------------------------
//
//                      ENEMY KILLS
// 
//--------------------------------------------------------------


void CheckCollision(Shoot* shoot, Enemy* enemy) {
	if (CheckCollisionRecs(shoot->position, enemy->position)) {
		enemy->hp -= shoot->damage;
		shoot->active = false;
		if (enemy->hp <= 0) {
			enemy->active = false;
			enemies_killed++;
			level_up_flag = AddToExp(enemy->exp);
            if (level_up_flag) PowerRandomizer();
			player_score += 10;
		}
	}
}

// Function to check and handle bullet and enemy collisions
void CheckBulletAndEnemyCollision(Enemy* enemy) {
    for (int i = 0; i < 50; i++) {
        if (!enemy[i].active) continue;

        for (int j = 0; j < 50; j++) {
 
            // PULSE
            if (IsPulseActive()) {
				Shoot* shoot = GetPulseShoot(j);
				if (shoot->active) CheckCollision(shoot, &enemy[i]);
            }
            
			// PHOTON
            if (IsPhotonActive()) {
				Shoot* shoot = GetPhotonShoot(j);
				if (shoot->active) CheckCollision(shoot, &enemy[i]);
            }
        }
    }
}

//--------------------------------------------------------------
//
//                         UPDATE
// 
//--------------------------------------------------------------

void UpdateBackground(Background* background) {
    if (background->alpha < 0.7) background->alpha += 0.2f * GetFrameTime();
    background->position_y = (float)(fmod(background->position_y + 75 * GetFrameTime(), 2400));
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
        if (IsKeyPressed(KEY_SPACE)) {
            printf("opa\n");
        }
        UpdateWaveAlpha();

        if (level_up_flag) {
            UpdateLevelUpSelectMenu(&level_up_flag);
        } else {
            UpdateWave();
            UpdateBackground(&background);

            UpdatePlayer(&player);
            UpdateWeapon(&player);
            UpdateEnemies(enemy);
            CheckBulletAndEnemyCollision(enemy); // Enemy, kills and score
            UpdateExpBar();

            if (CheckEnemyCollisionWithPlayer(player, enemy)) ChangeScene(ENTER_NAME);
        }
    }
}


//--------------------------------------------------------------
//
//                         DRAW
// 
//--------------------------------------------------------------

void DrawBackground() {
    DrawTexture(background.texture, (int)background.position_x, (int)background.position_y, Fade(background.color, background.alpha));
    DrawTexture(background.texture, (int)(background.position_x), (int)(background.position_y) - 2400, Fade(background.color, background.alpha));
}

void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawBackground();
	DrawWeapon(&player);
    DrawPlayer(player);
    DrawEnemies(enemy);
    DrawExpBar();
    DrawLevelUpSelectMenu(level_up_flag);

    if (active_wave == FIRST_WAVE) DrawText("FIRST WAVE", SCREEN_WIDTH / 2 - MeasureText("FIRST WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 100, 40, Fade(WHITE, wave_message_alpha));
    else if (active_wave == SECOND_WAVE) DrawText("SECOND WAVE", SCREEN_WIDTH / 2 - MeasureText("SECOND WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 100, 40, Fade(WHITE, wave_message_alpha));
    else if (active_wave == THIRD_WAVE) DrawText("THIRD WAVE", SCREEN_WIDTH / 2 - MeasureText("THIRD WAVE", 40) / 2, SCREEN_HEIGHT / 2 - 100, 40, Fade(WHITE, wave_message_alpha));

    DrawText(TextFormat("%04i", player_score), 20, 20, 40, GRAY);
    
    if (victory) DrawText("YOU WIN", SCREEN_WIDTH / 2 - MeasureText("YOU WIN", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, WHITE);
    if (pause) DrawText("GAME PAUSED", SCREEN_WIDTH / 2 - MeasureText("GAME PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 40, 40, GRAY);

    EndDrawing();
}

//--------------------------------------------------------------
//
//                     LEVEL UP
// 
//--------------------------------------------------------------



//--------------------------------------------------------------
//
//                     LOAD | UNLOAD
// 
//--------------------------------------------------------------

void LoadGameTextures(void) {
    background.texture = LoadTexture("purplebg.png");
}

void UnloadGameTextures(void) {
    UnloadTexture(background.texture);
}