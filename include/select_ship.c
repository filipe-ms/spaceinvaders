// select_ship.c

#include "select_ship.h"
#include "math.h"
#include "player.h"

SelectMenuShip ship_1;
SelectMenuBackground select_menu_background;
SelectMenuOption current_select_menu_option;

bool select_alpha_flag = true;
bool select_transition_complete = false;

// Transition variables
float select_transition_duration_s = 5;
float select_transition_acceleration = 75;
float select_transition_speed = 75;
float select_transition_count = 0;
float select_transition_alpha_text = 0;
float select_transition_alpha_increment = 0.2;

void InitSelectMenu() {
    current_select_menu_option = MIDDLE_SHIP;
    select_menu_background.color = WHITE;
    select_menu_background.alpha = 0.0f;
    select_menu_background.y_offset = 0;

    ship_1.alpha = 0.0f;
    ship_1.color = WHITE;
    ship_1.sprite_location = (Rectangle){ 8, 0, 8, 8 };
    ship_1.sprite_destination = (Rectangle){ SCREEN_WIDTH / 2 - 32, 400, 64, 64 };
}

void UpdateSelectMenu(GameScreen* game_screen) {
    if (select_menu_background.alpha < 1) select_menu_background.alpha += 0.25f * GetFrameTime();
    if (ship_1.alpha < 1) ship_1.alpha += 0.25f * GetFrameTime();
    if (select_transition_alpha_text < 1) select_transition_alpha_text += 0.25f * GetFrameTime();

    select_menu_background.y_offset = fmod(select_menu_background.y_offset + 75 * GetFrameTime(), 1200);
    if (IsKeyPressed(KEY_LEFT)) {
        current_select_menu_option = (current_select_menu_option - 1 + SELECT_MENU_OPTION_COUNT) % SELECT_MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        current_select_menu_option = (current_select_menu_option + 1) % SELECT_MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        *game_screen = TUTORIAL_TRANSITION;
    }
}

void DrawSelectMenuBackground() {
    if (select_alpha_flag) {
        select_menu_background.alpha += 0.1f * GetFrameTime();
        if (select_menu_background.alpha >= 0.8f) select_alpha_flag = false;
    }
    else {
        select_menu_background.alpha -= 0.1f * GetFrameTime();
        if (select_menu_background.alpha <= 0.6f) select_alpha_flag = true;
    }

    DrawTexture(select_menu_background.texture, 0, select_menu_background.y_offset, Fade(WHITE, select_menu_background.alpha));
    DrawTexture(select_menu_background.texture, 0, select_menu_background.y_offset-1200, Fade(WHITE, select_menu_background.alpha));
}

void DrawSelectMenu() {
    BeginDrawing();

    ClearBackground(BLACK);

    DrawSelectMenuBackground();

    Color titleColor = Fade(RAYWHITE, select_transition_alpha_text);

    Color colorStart = (current_select_menu_option == LEFT_SHIP) ? Fade(RED, select_transition_alpha_text) : Fade(GRAY, select_transition_alpha_text);
    Color colorRanking = (current_select_menu_option == MIDDLE_SHIP) ? Fade(RED, select_transition_alpha_text) : Fade(GRAY, select_transition_alpha_text);
    Color colorExit = (current_select_menu_option == RIGHT_SHIP) ? Fade(RED, select_transition_alpha_text) : Fade(GRAY, select_transition_alpha_text);

    DrawTexturePro(ship_1.texture, ship_1.sprite_location, ship_1.sprite_destination, (Vector2) { 0, 0 }, 0, Fade(WHITE, ship_1.alpha));

    DrawText("Unavailable", SCREEN_WIDTH*0.25 - MeasureText("Unavailable", 20) / 2, 500, 20, colorStart);
    DrawText("NomeNave", SCREEN_WIDTH/2 - MeasureText("NomeNave", 20) / 2, 500, 20, colorRanking);
    DrawText("Unavailable", SCREEN_WIDTH*0.75 - MeasureText("Unavailable", 20) / 2, 500, 20, colorExit);
    EndDrawing();
}

void LoadSelectMenuTextures() {
    select_menu_background.texture = LoadTexture("shipselectbg.png");
    ship_1.texture = LoadTexture("ships.png");
}

void UnloadSelectMenuTextures() {
    UnloadTexture(select_menu_background.texture);
}

void UpdateSelectMenuTransition() {
    select_transition_count += GetFrameTime();
    select_transition_speed += select_transition_acceleration * GetFrameTime();
    select_transition_acceleration += select_transition_acceleration * GetFrameTime();
    select_menu_background.y_offset = fmod(select_menu_background.y_offset + select_transition_speed * GetFrameTime(), 1200);
    select_transition_alpha_text -= select_transition_alpha_increment * 2 * GetFrameTime();
    select_menu_background.alpha -= select_transition_alpha_increment * GetFrameTime();
    
    if (ship_1.sprite_destination.y <= SCREEN_HEIGHT - 100) {
        ship_1.sprite_destination.y += 180 * GetFrameTime();
    }
        

    if (select_transition_count >= 5) select_transition_complete = true;
}

bool SelectMenuTransition() {
    UpdateSelectMenuTransition();
    DrawSelectMenu();
    return select_transition_complete;
}
void SetSelectTransitionFalse() {
    select_transition_complete = false;
}