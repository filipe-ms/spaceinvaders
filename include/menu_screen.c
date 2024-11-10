// menu_screen.c

#include "menu_screen.h"
#include "math.h"

MenuBackground menu_background;
MenuOption current_option;

bool alpha_flag = true;
bool transition_complete = false;

// Transition variables
float transition_duration_s = 5;
float transition_acceleration = 75;
float transition_speed = 75;
float transition_count = 0;
float transition_alpha_text = 1;
float transition_alpha_increment = 0.2;

void InitMenu() {
    current_option = MENU_OPTION_START;
    menu_background.color = WHITE;
    menu_background.alpha = 0.4f;
    menu_background.y_offset = 0;
}

void UpdateMenu(GameScreen* game_screen) {
    menu_background.y_offset = fmod(menu_background.y_offset + 75 * GetFrameTime(), 1200);
    if (IsKeyPressed(KEY_UP)) {
        current_option = (current_option - 1 + MENU_OPTION_COUNT) % MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_DOWN)) {
        current_option = (current_option + 1) % MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        if (current_option == MENU_OPTION_START) {
            *game_screen = SELECT_TRANSITION;
        }
        else if (current_option == MENU_OPTION_RANKING) {
            *game_screen = RANKING;
        }
        else if (current_option == MENU_OPTION_EXIT) {
            *game_screen = EXIT;
        }
    }
}

void DrawMenuBackground() {
    if (alpha_flag) {
        menu_background.alpha += 0.1f * GetFrameTime();
        if (menu_background.alpha >= 0.8f) alpha_flag = false;
    }
    else {
        menu_background.alpha -= 0.1f * GetFrameTime();
        if (menu_background.alpha <= 0.6f) alpha_flag = true;
    }

    DrawTexture(menu_background.texture, 0, menu_background.y_offset, Fade(WHITE, menu_background.alpha));
    DrawTexture(menu_background.texture, 0, menu_background.y_offset-1200, Fade(WHITE, menu_background.alpha));
}

void DrawMenu() {
    BeginDrawing();

    ClearBackground(BLACK);

    DrawMenuBackground();

    Color titleColor = Fade(RAYWHITE, transition_alpha_text);
    DrawText("SPACE INVADERS", SCREEN_WIDTH / 2 - MeasureText("SPACE INVADERS", 50) / 2, 400, 50, titleColor);

    Color colorStart = (current_option == MENU_OPTION_START) ? Fade(RED, transition_alpha_text) : Fade(GRAY, transition_alpha_text);
    Color colorRanking = (current_option == MENU_OPTION_RANKING) ? Fade(RED, transition_alpha_text) : Fade(GRAY, transition_alpha_text);
    Color colorExit = (current_option == MENU_OPTION_EXIT) ? Fade(RED, transition_alpha_text) : Fade(GRAY, transition_alpha_text);

    DrawText("Game Start", SCREEN_WIDTH / 2 - MeasureText("Game Start", 30) / 2, 500, 30, colorStart);
    DrawText("Ranking", SCREEN_WIDTH / 2 - MeasureText("Ranking", 30) / 2, 550, 30, colorRanking);
    DrawText("Exit", SCREEN_WIDTH / 2 - MeasureText("Exit", 30) / 2, 600, 30, colorExit);
    EndDrawing();
}

void LoadMenuBackgroundTexture() {
    menu_background.texture = LoadTexture("menubg.png");
}

void UnloadMenuBackgroundTexture() {
    UnloadTexture(menu_background.texture);
}

void UpdateMenuTransition() {
    transition_count += GetFrameTime();
    transition_speed += transition_acceleration * GetFrameTime();
    transition_acceleration += transition_acceleration * GetFrameTime();
    menu_background.y_offset = fmod(menu_background.y_offset + transition_speed * GetFrameTime(), 1200);
    transition_alpha_text -= transition_alpha_increment * 2 * GetFrameTime();
    menu_background.alpha -= transition_alpha_increment * GetFrameTime();
    if (transition_count >= 4) transition_complete = true;
}

bool MenuTransition() {
    UpdateMenuTransition();
    DrawMenu();
    return transition_complete;
}

void SetTransitionFalse() {
    transition_complete = false;
}