// main_menu.c

#include "main_menu.h"
#include "draw_object.h"
#include "common.h"
#include "scene_manager.h"
#include <math.h>

// Background
Background background;
bool alpha_flag = true;

// Option
MenuOption current_option;
Scene scene;

// Transition variables
float transition_duration_s = 2.0f;
float transition_acceleration = 200.0f;
float transition_speed = 120.0f;
float transition_count = 0.0f;
float transition_alpha_text = 1.0f;
float transition_alpha_increment = 0.6f;
bool transition_complete = false;
bool is_transitioning = false;

void InitMenu() {
    current_option = MENU_OPTION_START;
    background.color = WHITE;
    background.alpha = 0.6f;
    background.position_y = 0;

    transition_acceleration = 200.0f;
    transition_speed = 120.0f;
    transition_count = 0.0f;
    transition_alpha_text = 1.0f;
    transition_alpha_increment = 0.6f;

    transition_complete = false;
    is_transitioning = false;
}

void UpdateMenuTransition() {
    transition_count += GetFrameTime();
    transition_speed += transition_acceleration * GetFrameTime();
    transition_acceleration += transition_acceleration * GetFrameTime();
    background.position_y = (float)fmod(background.position_y + transition_speed * GetFrameTime(), 1200);
    transition_alpha_text -= transition_alpha_increment * 2 * GetFrameTime();
    background.alpha -= transition_alpha_increment * GetFrameTime();

    if (transition_count >= transition_duration_s) transition_complete = true;
}

void UpdateMainMenuBackground() {
    if (alpha_flag) {
        background.alpha += 0.2f * GetFrameTime();
        if (background.alpha >= 0.8f) alpha_flag = false;
    }
    else {
        background.alpha -= 0.2f * GetFrameTime();
        if (background.alpha <= 0.4f) alpha_flag = true;
    }
}

void UpdateMenu() {

    if (transition_complete) {
        ChangeScene(scene);
        return;
    }

    if (is_transitioning) {
        UpdateMenuTransition();
        return;
    }

    UpdateMainMenuBackground();

    background.position_y = (float)fmod(background.position_y + 100 * GetFrameTime(), 1200);

    if (IsKeyPressed(KEY_UP)) {
        current_option = (current_option - 1 + MENU_OPTION_COUNT) % MENU_OPTION_COUNT;
    }

    else if (IsKeyPressed(KEY_DOWN)) {
        current_option = (current_option + 1) % MENU_OPTION_COUNT;
    }

    else if (IsKeyPressed(KEY_ENTER)) {
        if (current_option == MENU_OPTION_START) {
            scene = SELECT_SHIP;
            is_transitioning = true;
        }
        else if (current_option == MENU_OPTION_RANKING) {
            scene = RANKING;
            is_transitioning = true;
        }
        else if (current_option == MENU_OPTION_EXIT) {
            is_transitioning = true;
            scene = EXIT;
        }
    }
}

void DrawMenuBackground() {
    DrawTexture(background.texture, 0, (int)background.position_y, Fade(WHITE, background.alpha));
    DrawTexture(background.texture, 0, (int)(background.position_y-1200), Fade(WHITE, background.alpha));
}

void DrawMenu() {
    BeginDrawing();

    ClearBackground(BLACK);

    DrawMenuBackground();

    Color titleColor = Fade(RAYWHITE, transition_alpha_text);
    DrawText("SPACE INVADERS", SCREEN_WIDTH / 2 - MeasureText("SPACE INVADERS", 50) / 2, 300, 50, titleColor);

    Color colorStart = (current_option == MENU_OPTION_START) ? Fade(RED, transition_alpha_text) : Fade(GRAY, transition_alpha_text);
    Color colorRanking = (current_option == MENU_OPTION_RANKING) ? Fade(RED, transition_alpha_text) : Fade(GRAY, transition_alpha_text);
    Color colorCredits = (current_option == MENU_OPTION_CREDITS) ? Fade(RED, transition_alpha_text) : Fade(GRAY, transition_alpha_text);
    Color colorExit = (current_option == MENU_OPTION_EXIT) ? Fade(RED, transition_alpha_text) : Fade(GRAY, transition_alpha_text);

    DrawText("Game Start", SCREEN_WIDTH / 2 - MeasureText("Game Start", 30) / 2, 400, 30, colorStart);
    DrawText("Ranking", SCREEN_WIDTH / 2 - MeasureText("Ranking", 30) / 2, 450, 30, colorRanking);
    DrawText("Credits", SCREEN_WIDTH / 2 - MeasureText("Credits", 30) / 2, 500, 30, colorCredits);
    DrawText("DLC DISPONIVEL", SCREEN_WIDTH *0.85 - MeasureText("DLC DISPONIVEL", 20) / 2, 920, 20, WHITE);
    DrawText("Exit", SCREEN_WIDTH / 2 - MeasureText("Exit", 30) / 2, 550, 30, colorExit);

    EndDrawing();
}

void LoadMenuBackgroundTexture() {
    background.texture = LoadTexture("menubg.png");
}

void UnloadMenuBackgroundTexture() {
    UnloadTexture(background.texture);
}