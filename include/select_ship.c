// select_ship.c

#include "select_ship.h"
#include "math.h"
#include "player.h"
#include "scene_manager.h"
#include "draw_object.h"
#include "commons.h"

Background select_ship_menu_background;
SelectMenuOption select_ship_menu_option;

bool select_ship_alpha_flag = true;

Orion orion;
float anim_cycle;
Scene scene;

// Transition variables
float select_ship_transition_duration_s = 5.0f;
float select_ship_transition_acceleration = 75.0f;
float select_ship_transition_speed = 75.0f;
float select_ship_transition_count = 0.0f;
float select_ship_transition_alpha_text = 0.0f;
float select_ship_transition_alpha_increment = 0.2f;
bool select_ship_menu_is_transitioning = false;
bool select_ship_menu_transition_complete = false;

void InitSelectMenu() {
    select_ship_menu_option = MIDDLE_SHIP;
    select_ship_menu_background.color = WHITE;
    select_ship_menu_background.alpha = 0.0f;
    select_ship_menu_background.position_x = 0;
    select_ship_menu_background.position_y = 0;
    

    select_ship_transition_acceleration = 75.0f;
    select_ship_transition_speed = 75.0f;
    select_ship_transition_count = 0.0f;
    select_ship_transition_alpha_text = 0.0f;
    select_ship_transition_alpha_increment = 0.2f;
    select_ship_menu_is_transitioning = false;
    select_ship_menu_transition_complete = false;

    orion.destination = (Rectangle){ SCREEN_WIDTH / 2 - 32, 400, 64, 64 };
    orion.direction = 0;
    orion.thruster_cycle = 0;
    orion.color = WHITE;
    orion.alpha = 0.0f;
}

void UpdateSelectShipMenuAnimationCycle() {
    anim_cycle += 0.2f * GetFrameTime();
    if (anim_cycle > 1.0f)anim_cycle -= 1.0f;
}

int GetSelectShipMenuThrusterAnimationCycle() {
    if (anim_cycle < 0.25f) return 1;
    if (anim_cycle < 0.5f) return 2;
    if (anim_cycle < 0.75f) return 3;
    return 4;
}

void UpdateSelectShipMenuOrion() {
    orion.thruster_cycle = GetSelectShipMenuThrusterAnimationCycle();
}

void UpdateShipSelectMenuTransition() {
    select_ship_transition_count += GetFrameTime();
    select_ship_transition_speed += select_ship_transition_acceleration * GetFrameTime();
    select_ship_transition_acceleration += select_ship_transition_acceleration * GetFrameTime();
    select_ship_menu_background.position_y = (float)(fmod(select_ship_menu_background.position_y + select_ship_transition_speed * GetFrameTime(), 1200));
    select_ship_transition_alpha_text -= select_ship_transition_alpha_increment * 2 * GetFrameTime();
    select_ship_menu_background.alpha -= select_ship_transition_alpha_increment * GetFrameTime();

    if (orion.destination.y <= SCREEN_HEIGHT - 100) {
        orion.destination.y += 180 * GetFrameTime();
    }

    if (select_ship_transition_count >= 5) select_ship_menu_transition_complete = true;
}

void UpdateShipSelectMenu() {
    UpdateSelectShipMenuAnimationCycle();
    UpdateSelectShipMenuOrion();

    if (select_ship_menu_transition_complete) {
        ChangeScene(scene);
        return;
    }

    if (select_ship_menu_is_transitioning) {
        UpdateShipSelectMenuTransition();
        return;
    }

    if (select_ship_menu_background.alpha < 1) select_ship_menu_background.alpha += 0.25f * GetFrameTime();
    if (orion.alpha < 1) orion.alpha += 0.25f * GetFrameTime();
    if (select_ship_transition_alpha_text < 1) select_ship_transition_alpha_text += 0.25f * GetFrameTime();

    select_ship_menu_background.position_y = (float)fmod(select_ship_menu_background.position_y + 75 * GetFrameTime(), 1200);
    if (IsKeyPressed(KEY_LEFT)) {
        select_ship_menu_option = (select_ship_menu_option - 1 + SELECT_MENU_OPTION_COUNT) % SELECT_MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        select_ship_menu_option = (select_ship_menu_option + 1) % SELECT_MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        select_ship_menu_is_transitioning = true;
        scene = GAME;
    }
}

void DrawSelectMenuBackground() {
    if (select_ship_alpha_flag) {
        select_ship_menu_background.alpha += 0.1f * GetFrameTime();
        if (select_ship_menu_background.alpha >= 0.8f) select_ship_alpha_flag = false;
    }
    else {
        select_ship_menu_background.alpha -= 0.1f * GetFrameTime();
        if (select_ship_menu_background.alpha <= 0.6f) select_ship_alpha_flag = true;
    }

    DrawTexture(select_ship_menu_background.texture, 0, (int)(select_ship_menu_background.position_y), Fade(WHITE, select_ship_menu_background.alpha));
    DrawTexture(select_ship_menu_background.texture, 0, (int)(select_ship_menu_background.position_y)-1200, Fade(WHITE, select_ship_menu_background.alpha));
}

void DrawSelectMenu() {
    BeginDrawing();

    ClearBackground(BLACK);

    DrawSelectMenuBackground();

    Color colorStart = (select_ship_menu_option == LEFT_SHIP) ? Fade(RED, select_ship_transition_alpha_text) : Fade(GRAY, select_ship_transition_alpha_text);
    Color colorRanking = (select_ship_menu_option == MIDDLE_SHIP) ? Fade(RED, select_ship_transition_alpha_text) : Fade(GRAY, select_ship_transition_alpha_text);
    Color colorExit = (select_ship_menu_option == RIGHT_SHIP) ? Fade(RED, select_ship_transition_alpha_text) : Fade(GRAY, select_ship_transition_alpha_text);

    DrawOrion(&orion);

    char* unavailable = "Unavailable";
    char* orion = "Orion";

    DrawText(unavailable, (int)(SCREEN_WIDTH*0.25f - MeasureText(unavailable, 20) / 2.0f), 500, 20, colorStart);
    DrawText(orion, (int)(SCREEN_WIDTH/2.0f - MeasureText(orion, 20) / 2.0f), 500, 20, colorRanking);
    DrawText(unavailable, (int)(SCREEN_WIDTH*0.75f - MeasureText(unavailable, 20) / 2.0f), 500, 20, colorExit);
    EndDrawing();
}

void LoadSelectMenuTextures() {
    select_ship_menu_background.texture = LoadTexture("shipselectbg.png");
}

void UnloadSelectMenuTextures() {
    UnloadTexture(select_ship_menu_background.texture);
}