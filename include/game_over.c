#include "game_over.h"
#include "raylib.h"
#include "scene_manager.h"
#include "common.h"
#include "select_ship.h"
#include "winner.h"

float game_over_alpha = 1.0f;
bool game_over_enter_transition = true;
bool game_over_leave_transition = false;


void InitGameOver(void) {
    game_over_alpha = 1.0f;
    game_over_enter_transition = true;
    game_over_leave_transition = false;
}

void UpdateGameOver(void) {
    if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
        game_over_leave_transition = true;
    }

    if (game_over_enter_transition && !game_over_leave_transition) {
        game_over_alpha -= 0.5f * GetFrameTime();
        if (game_over_alpha <= 0) {
            game_over_alpha = 0;
            game_over_enter_transition = false;
        }
    }
    else if (game_over_leave_transition) {
        game_over_alpha += 0.5f * GetFrameTime();
        if (game_over_alpha >= 1) {
            game_over_alpha = 1;
            game_over_leave_transition = false;

            if (GetScore() > 0) {
                ChangeScene(ENTER_NAME);
            }
            else {
                ChangeScene(RANKING);
            }
        }
    }
}


void DrawGameOver(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Game Over", GetScreenWidth() / 2 - MeasureText("Game Over", 40) / 2, GetScreenHeight() / 2 - 160, 40, WHITE);
    DrawText("Pressione Enter ou 'A' para continuar", GetScreenWidth() / 2 - MeasureText("Pressione Enter ou 'A' para continuar", 20) / 2, GetScreenHeight() / 2, 20, WHITE);
    DrawSelectMenuBackground();
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, game_over_alpha));
    EndDrawing();
}
