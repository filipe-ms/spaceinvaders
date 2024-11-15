// select_ship.c

#include "select_ship.h"
#include "common.h"
#include "player.h"
#include "scene_manager.h"
#include "draw_object.h"
#include <math.h>

Background select_ship_menu_background;
SelectMenuOption select_ship_menu_option;
SelectMenuOption selected_ship;

bool select_ship_alpha_flag = true;

Orion orion;
Aurea aurea;
Nebula nebula;
float anim_cycle;

Scene scene;

// Transition variables
float select_ship_transition_duration_s = 1.7f;
float select_ship_transition_acceleration = 200.0f;
float select_ship_transition_speed = 120.0f;
float select_ship_transition_count = 0.0f;
float select_ship_transition_alpha_text = 0.0f;
float select_ship_transition_alpha_increment = 0.4f;
bool select_ship_menu_is_transitioning = false;
bool select_ship_menu_transition_complete = false;

void InitSelectMenu() {
    select_ship_menu_option = MIDDLE_SHIP;
    select_ship_menu_background.color = WHITE;
    select_ship_menu_background.alpha = 0.0f;
    select_ship_menu_background.position_x = 0;
    select_ship_menu_background.position_y = 0;
    
    select_ship_transition_acceleration = 200.0f;
    select_ship_transition_speed = 120.0f;
    select_ship_transition_count = 0.0f;
    select_ship_transition_alpha_text = 0.0f;
    select_ship_transition_alpha_increment = 0.5f;
    select_ship_menu_is_transitioning = false;
    select_ship_menu_transition_complete = false;

    // Init Aurea
    aurea.destination = (Rectangle){ SCREEN_WIDTH * 0.25 - 22, 308, 64, 64 };
    aurea.direction = 0;
    aurea.thruster_cycle = 0;
    aurea.color = WHITE;
    aurea.alpha = 0.0f;

	// Init Orion
    orion.destination = (Rectangle){ SCREEN_WIDTH / 2 - 23, 310, 64, 64 };
    orion.direction = 0;
    orion.thruster_cycle = 0;
    orion.color = WHITE;
    orion.alpha = 0.0f;

    // Init Nebula
    nebula.destination = (Rectangle){ SCREEN_WIDTH * 0.75 - 22, 308, 64, 64 };
    nebula.direction = 0;
    nebula.thruster_cycle = 0;
    nebula.color = WHITE;
    nebula.alpha = 0.0f;
}

void UpdateSelectShipMenuAnimationCycle() {
    anim_cycle += 0.5f * GetFrameTime();
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

void UpdateSelectShipMenuAurea() {
    aurea.thruster_cycle = GetSelectShipMenuThrusterAnimationCycle();
}

void UpdateSelectShipMenuNebula() {
    nebula.thruster_cycle = GetSelectShipMenuThrusterAnimationCycle();
}

void UpdateShipSelectMenuTransition() {
    select_ship_transition_count += GetFrameTime();
    select_ship_transition_speed += select_ship_transition_acceleration * GetFrameTime();
    select_ship_transition_acceleration += select_ship_transition_acceleration * GetFrameTime();
    select_ship_menu_background.position_y = (float)(fmod(select_ship_menu_background.position_y + select_ship_transition_speed * GetFrameTime(), 1200));
    select_ship_transition_alpha_text -= select_ship_transition_alpha_increment * 2 * GetFrameTime();
    select_ship_menu_background.alpha -= select_ship_transition_alpha_increment * GetFrameTime();

	if (selected_ship == ORION) {
		if (orion.destination.y >= -1 * SCREEN_HEIGHT) {
			orion.destination.y -= 1000 * GetFrameTime();
			aurea.alpha -= 1.0f * GetFrameTime();
			nebula.alpha -= 1.0f * GetFrameTime();
		}
	}
	else if (selected_ship == AUREA) {
		if (aurea.destination.y >= -1 * SCREEN_HEIGHT) {
			aurea.destination.y -= 1000 * GetFrameTime();
			orion.alpha -= 1.0f * GetFrameTime();
			nebula.alpha -= 1.0f * GetFrameTime();
		}
	}
	else if (selected_ship == NEBULA) {
        if (nebula.destination.y >= -1 * SCREEN_HEIGHT) {
			nebula.destination.y -= 1000 * GetFrameTime();
            aurea.alpha -= 1.0f * GetFrameTime();
			orion.alpha -= 1.0f * GetFrameTime();
		}
	}

    if (select_ship_transition_count >= select_ship_transition_duration_s) select_ship_menu_transition_complete = true;
}

void UpdateShipSelectMenu() {

    UpdateSelectShipMenuAnimationCycle();
    UpdateSelectShipMenuOrion();
    UpdateSelectShipMenuAurea();
    UpdateSelectShipMenuNebula();

    if (select_ship_menu_transition_complete) {
        ChangeSceneArgs(scene, selected_ship);
        return;
    }

    if (select_ship_menu_is_transitioning) {
        UpdateShipSelectMenuTransition();
        return;
    }


    select_ship_menu_background.position_y = (float)fmod(select_ship_menu_background.position_y + 100 * GetFrameTime(), 1200);
    if (select_ship_menu_background.alpha < 0.8f) select_ship_menu_background.alpha += 0.25f * GetFrameTime();

    if (orion.alpha < 1) orion.alpha += 0.75f * GetFrameTime();
    if (aurea.alpha < 1) aurea.alpha += 0.75f * GetFrameTime();
    if (nebula.alpha < 1) nebula.alpha += 0.75f * GetFrameTime();

    if (select_ship_transition_alpha_text < 1) select_ship_transition_alpha_text += 0.25f * GetFrameTime();

    if (IsKeyPressed(KEY_LEFT)) {
        select_ship_menu_option = (select_ship_menu_option - 1 + SELECT_MENU_OPTION_COUNT) % SELECT_MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_RIGHT)) {
        select_ship_menu_option = (select_ship_menu_option + 1) % SELECT_MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_ENTER)) {
		selected_ship = select_ship_menu_option;
        select_ship_menu_is_transitioning = true;
        scene = TUTORIAL;
    }
}

void DrawSelectMenuBackground(void) {
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

    Color ship_1 = (select_ship_menu_option == LEFT_SHIP) ? Fade(RED, select_ship_transition_alpha_text) : Fade(GRAY, select_ship_transition_alpha_text);
    Color ship_2 = (select_ship_menu_option == MIDDLE_SHIP) ? Fade(RED, select_ship_transition_alpha_text) : Fade(GRAY, select_ship_transition_alpha_text);
    Color ship_3 = (select_ship_menu_option == RIGHT_SHIP) ? Fade(RED, select_ship_transition_alpha_text) : Fade(GRAY, select_ship_transition_alpha_text);

    DrawAurea(&aurea);
    DrawOrion(&orion);
	DrawNebula(&nebula);

    char* left_ship = "Aurea";
    char* middle_ship = "Orion";
    char* right_ship = "Nebula";

    DrawText(left_ship, (int)(SCREEN_WIDTH*0.25f - MeasureText(left_ship, 20) / 2.0f), 400, 20, ship_1);
    DrawText(middle_ship, (int)(SCREEN_WIDTH/2.0f - MeasureText(middle_ship, 20) / 2.0f), 400, 20, ship_2);
    DrawText(right_ship, (int)(SCREEN_WIDTH*0.75f - MeasureText(right_ship, 20) / 2.0f), 400, 20, ship_3);
    EndDrawing();
}

void LoadSelectMenuTextures() {
    select_ship_menu_background.texture = LoadTexture("shipselectbg.png");
}

void UnloadSelectMenuTextures() {
    UnloadTexture(select_ship_menu_background.texture);
}