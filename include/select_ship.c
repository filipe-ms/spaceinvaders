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

Orion select_orion;
Aurea select_aurea;
Nebula select_nebula;
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
    select_aurea.destination = (Rectangle){ SCREEN_WIDTH * 0.25 -32, 300, 64, 64 };
    select_aurea.direction = 0;
    select_aurea.thruster_cycle = 0;
    select_aurea.color = WHITE;
    select_aurea.alpha = 0.0f;

	// Init Orion
    select_orion.destination = (Rectangle){ SCREEN_WIDTH / 2 - 23, 310, 64, 64 };
    select_orion.direction = 0;
    select_orion.thruster_cycle = 0;
    select_orion.color = WHITE;
    select_orion.alpha = 0.0f;

    // Init Nebula
    select_nebula.destination = (Rectangle){ SCREEN_WIDTH * 0.75 - 22, 308, 64, 64 };
    select_nebula.direction = 0;
    select_nebula.thruster_cycle = 0;
    select_nebula.color = WHITE;
    select_nebula.alpha = 0.0f;
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
    select_orion.thruster_cycle = GetSelectShipMenuThrusterAnimationCycle();
}

void UpdateSelectShipMenuAurea() {
    select_aurea.thruster_cycle = GetSelectShipMenuThrusterAnimationCycle();
}

void UpdateSelectShipMenuNebula() {
    select_nebula.thruster_cycle = GetSelectShipMenuThrusterAnimationCycle();
}

void UpdateShipSelectMenuTransition() {
    select_ship_transition_count += GetFrameTime();
    select_ship_transition_speed += select_ship_transition_acceleration * GetFrameTime();
    select_ship_transition_acceleration += select_ship_transition_acceleration * GetFrameTime();
    select_ship_menu_background.position_y = (float)(fmod(select_ship_menu_background.position_y + select_ship_transition_speed * GetFrameTime(), 1200));
    select_ship_transition_alpha_text -= select_ship_transition_alpha_increment * 2 * GetFrameTime();
    select_ship_menu_background.alpha -= select_ship_transition_alpha_increment * GetFrameTime();

	if (selected_ship == ORION) {
		if (select_orion.destination.y >= -1 * SCREEN_HEIGHT) {
			select_orion.destination.y -= 1000 * GetFrameTime();
			select_aurea.alpha -= 1.0f * GetFrameTime();
			select_nebula.alpha -= 1.0f * GetFrameTime();
		}
	}
	else if (selected_ship == AUREA) {
		if (select_aurea.destination.y >= -1 * SCREEN_HEIGHT) {
			select_aurea.destination.y -= 1000 * GetFrameTime();
			select_orion.alpha -= 1.0f * GetFrameTime();
			select_nebula.alpha -= 1.0f * GetFrameTime();
		}
	}
	else if (selected_ship == NEBULA) {
        if (select_nebula.destination.y >= -1 * SCREEN_HEIGHT) {
			select_nebula.destination.y -= 1000 * GetFrameTime();
            select_aurea.alpha -= 1.0f * GetFrameTime();
			select_orion.alpha -= 1.0f * GetFrameTime();
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

    if (select_orion.alpha < 1) select_orion.alpha += 0.75f * GetFrameTime();
    if (select_aurea.alpha < 1) select_aurea.alpha += 0.75f * GetFrameTime();
    if (select_nebula.alpha < 1) select_nebula.alpha += 0.75f * GetFrameTime();

    if (select_ship_transition_alpha_text < 1) select_ship_transition_alpha_text += 0.25f * GetFrameTime();

    // Navegação com teclado e gamepad
    if (IsKeyPressed(KEY_LEFT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
        select_ship_menu_option = (select_ship_menu_option - 1 + SELECT_MENU_OPTION_COUNT) % SELECT_MENU_OPTION_COUNT;
    }
    else if (IsKeyPressed(KEY_RIGHT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
        select_ship_menu_option = (select_ship_menu_option + 1) % SELECT_MENU_OPTION_COUNT;
    }

    // Seleção com Enter ou botão "A" do gamepad
    else if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
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

    DrawAurea(&select_aurea);
    DrawOrion(&select_orion);
	DrawNebula(&select_nebula);

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