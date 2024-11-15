#include "game.h"
#include "enemy.h"
#include "common.h"
#include "weapon.h"
#include "xp_bar.h"
#include "power_ups.h"
#include "scene_manager.h"

#include <math.h>

// Waves
#define FIRST_WAVE 0
#define SECOND_WAVE 1
#define THIRD_WAVE 2
#define VICTORY 3

// GAME STATE
static bool pause = false;
static bool pause_flag = false;
static bool victory = false;
static bool wave_completed = true;

static Player player = { 0 };
static Enemy enemy[MAX_ENEMY_NUMBER] = { 0 };

// BACKGROUND
static Background background;

// WAVE
int active_wave;
float wave_message_alpha;
bool wave_message_alpha_flag;

// WAVE INFO
float wave_duration_s = 60.0f;
float wave_enemy_cooldown_s = 5.0f;
float wave_enemy_charge_s = 0.0f;

// COUNTS
int player_score;
int enemies_killed;
int enemy_hp;

// BUFFS AND POWERS
bool level_up_flag = false;

void InitGame(int ship_id) {

    static bool pause = false;
    static bool pause_flag = false;
    static bool victory = false;
    wave_completed = true;

    // Special Conditions
    pause = false;
    pause_flag = false;
    victory = false;

    // Wave durations
    wave_duration_s = 60.0f;
    wave_enemy_cooldown_s = 4.5f;
    wave_enemy_charge_s = 0.0f;

    // Wave
    active_wave = FIRST_WAVE;
    wave_message_alpha = 0.1f;
    wave_message_alpha_flag = false;

    // Enemies
    enemies_killed = 0;
    player_score = 0;
    enemy_hp = 3;

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
    if (!wave_message_alpha_flag && wave_message_alpha>0) {
        wave_message_alpha += 0.5f * GetFrameTime();
        if (wave_message_alpha > 1.0f) wave_message_alpha = 1.0f;
    }
    else if (wave_message_alpha_flag) {
        wave_message_alpha -= 0.5f * GetFrameTime();
        if (wave_message_alpha < 0.0f) {
            wave_message_alpha = 0.0f;
            wave_completed = false;
        }
    }
}

void FirstWave() {
    UpdateWaveAlpha();

    if (wave_duration_s > 52) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnEnemies(enemy, 4, 0, 3);
            wave_enemy_cooldown_s -= 0.02f;
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
	}

	else if (wave_duration_s > 37) {
		if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnEnemies(enemy, 3, 0, 3);
            SpawnEnemies(enemy, 1, 1, 3);
            wave_enemy_cooldown_s -= 0.02f;
			wave_enemy_charge_s = -wave_enemy_cooldown_s;
		}
	}

	else if (wave_duration_s > 20) {
		if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnEnemies(enemy, 3, 0, 3);
            SpawnEnemies(enemy, 1, 1, 3);
			SpawnEnemies(enemy, 1, 2, 3);
            wave_enemy_cooldown_s -= 0.02f;
			wave_enemy_charge_s = -wave_enemy_cooldown_s;
		}
	}

	else if (wave_duration_s > 10) {
		if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnEnemies(enemy, 2, 0, 3);
			SpawnEnemies(enemy, 1, 1, 3);
            SpawnRandomEnemies(enemy, 3, 3);
            wave_enemy_cooldown_s -= 0.02f;
			wave_enemy_charge_s = -wave_enemy_cooldown_s;
		}
	}
	wave_enemy_charge_s += GetFrameTime();
	wave_duration_s -= GetFrameTime();

    if (wave_duration_s <= 0) {
        active_wave = SECOND_WAVE;
		wave_duration_s = 60.0f;
        wave_completed = true;
        wave_message_alpha = 0.1f;
    }
}

void SecondWave() {
    UpdateWaveAlpha();

    if (wave_duration_s > 52) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnEnemies(enemy, 2, 0, 4);
            SpawnEnemies(enemy, 1, 1, 4);
            SpawnRandomEnemies(enemy, 3, 4);
            wave_enemy_cooldown_s -= 0.03f;
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
    }

    else if (wave_duration_s > 37) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnEnemies(enemy, 1, 0, 4);
            SpawnEnemies(enemy, 1, 1, 4);
            SpawnRandomEnemies(enemy, 3, 4);
            wave_enemy_cooldown_s -= 0.03f;
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
    }
    else if (wave_duration_s > 32) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnEnemies(enemy, 3, 3, 4);
            SpawnRandomEnemies(enemy, 3, 4);
            wave_enemy_cooldown_s -= 0.03f;
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
    }

    else if (wave_duration_s > 20) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnRandomEnemies(enemy, 5, 4);
            wave_enemy_cooldown_s -= 0.03f;
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
    }

    else if (wave_duration_s > 10) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnRandomEnemies(enemy, 6, 4);
            wave_enemy_cooldown_s -= 0.03f;
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
    }

    wave_enemy_charge_s += GetFrameTime();
    wave_duration_s -= GetFrameTime();

    if (wave_duration_s <= 0) {
        active_wave = THIRD_WAVE;
        wave_duration_s = 60.0f;
        wave_completed = true;
        wave_message_alpha = 0.1f;
    }
}


void ThirdWave() {
    UpdateWaveAlpha();

    if (wave_duration_s > 30) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnRandomEnemies(enemy, 7, 5);
            wave_enemy_cooldown_s -= 0.03f;
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
    }

    else if (wave_duration_s > 0) {
        if (wave_enemy_charge_s >= wave_enemy_cooldown_s) {
            SpawnRandomEnemies(enemy, 10, 5);
            wave_enemy_charge_s = -wave_enemy_cooldown_s;
        }
    }

    wave_enemy_charge_s += GetFrameTime();
    wave_duration_s -= GetFrameTime();

    // Condition for next wave
    if (wave_duration_s<=0) {
        victory = true;
        active_wave = VICTORY;
        wave_completed = false;
        wave_completed = true;
        wave_message_alpha = 0.1f;
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
    for (int i = 0; i < MAX_ENEMY_NUMBER; i++) {
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

            // SHOTGUN
            if (IsShotgunActive()) {
                Shoot* shoot = GetShotgunShoot(j);
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
            UpdateEnemies(enemy, &player);
            CheckBulletAndEnemyCollision(enemy); // Enemy, kills and score
            UpdateExpBar();

            if (CheckEnemyCollisionWithPlayer(player, enemy)) ChangeScene(START);
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
//                     LOAD | UNLOAD
// 
//--------------------------------------------------------------

void LoadGameTextures(void) {
    background.texture = LoadTexture("purplebg.png");
}

void UnloadGameTextures(void) {
    UnloadTexture(background.texture);
}