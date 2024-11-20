// tutorial.c

#include "tutorial.h"
#include "scene_manager.h"
#include "common.h"
#include "select_ship.h"
#include "math.h"
#include "raymath.h"

#define FADE Fade(tutorial.color, tutorial.alpha * tutorial_transition_alpha * tutorial_start_alpha)

Background tutorial;

Texture power_1;
Texture power_2;
Texture power_3;

Texture weapon_1;
Texture weapon_2;
Texture weapon_3;

Texture keyboard_up;
Texture keyboard_down;
Texture keyboard_left;
Texture keyboard_right;

Texture keyboard_esc;
Texture keyboard_p;

bool tutorial_alpha_flag = true;
int id;

float tutorial_transition_alpha = 1.5;
bool tutorial_transition_flag = false;
float tutorial_start_alpha = 0.0;
bool tutorial_start_flag = true;

void InitTutorial(int ship_id) {
    id = ship_id;
    tutorial.position_y = 0;
    tutorial.position_x = 0;
    tutorial.color = WHITE;
    tutorial.alpha = 0.8;
    tutorial_alpha_flag = true;
    
    tutorial_transition_alpha = 1.5;
    tutorial_transition_flag = false;
    tutorial_start_flag = true;
    tutorial_start_alpha = 0.3;
}

void UpdateTutorialBackground() {
    if (tutorial_alpha_flag) {
        tutorial.alpha += 0.2f * GetFrameTime();
        if (tutorial.alpha >= 0.8f) tutorial_alpha_flag = false;
    }
    else {
        tutorial.alpha -= 0.2f * GetFrameTime();
        if (tutorial.alpha <= 0.4f) tutorial_alpha_flag = true;
    }
}

void UpdateTutorial(void) {
    if (tutorial_start_flag) {
        tutorial_start_alpha += 0.5 * GetFrameTime();
        if (tutorial_start_alpha >= 1) {
            tutorial_start_flag = false;
        }
    }
    if (IsKeyPressed(KEY_ENTER)) {
        tutorial_transition_flag = true;
    }
    if (tutorial_transition_flag) {
		tutorial_transition_alpha -= 0.5 * GetFrameTime();

    }
    if (tutorial_transition_alpha <= 0) {
        ChangeSceneArgs(GAME, id);
    }
    UpdateTutorialBackground();
}

float GetAlpha() {
    float time = GetTime();
    float alpha = (sinf(time * (2 * PI / 1.5)) + 1) / 2;
    return alpha;
}

void DrawTutorialBackground() {
    DrawTexture(tutorial.texture, 0, (int)tutorial.position_y, Fade(WHITE, tutorial.alpha));
}

void DrawTutorial() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(tutorial.texture, (int)(tutorial.position_x), (int)(tutorial.position_y), FADE);
	
    DrawText("Tutorial", SCREEN_WIDTH / 2 - MeasureText("Tutorial", 60) / 2, GetScreenHeight() - 920, 60, FADE);

    DrawText("Armas", SCREEN_WIDTH * 0.5 - MeasureText("Armas", 40)/2, GetScreenHeight() - 810, 40, FADE);
    
    DrawTextureEx(weapon_1, (Vector2) { SCREEN_WIDTH * 0.2 - (weapon_1.width / 1.25), GetScreenHeight() - 750 }, 0, 1.5, FADE);
    DrawText("Pulse", SCREEN_WIDTH * 0.2 - MeasureText("Pulse", 30) / 2, GetScreenHeight() - 670, 30, FADE);

    DrawTextureEx(weapon_2, (Vector2) { SCREEN_WIDTH * 0.5 - (weapon_2.width / 1.25), GetScreenHeight() - 750 }, 0, 1.5, FADE);
    DrawText("Photon", SCREEN_WIDTH * 0.5 - MeasureText("Photon", 30) / 2, GetScreenHeight() - 670, 30, FADE);

    DrawTextureEx(weapon_3, (Vector2) { SCREEN_WIDTH * 0.8 - (weapon_3.width / 1.25), GetScreenHeight() - 750 }, 0, 1.5, FADE);
    DrawText("Shotgun", SCREEN_WIDTH * 0.8 - MeasureText("Shotgun", 30) / 2, GetScreenHeight() - 670, 30, FADE);
    
    DrawText("Melhorias", SCREEN_WIDTH * 0.5 - MeasureText("Melhorias", 40) / 2, GetScreenHeight() - 580, 40, FADE);
    
    DrawTextureEx(power_1, (Vector2) { (SCREEN_WIDTH * 0.2) - (weapon_1.width / 1.25), GetScreenHeight() - 520 }, 0, 1.5, FADE);
    DrawText("Recarga", SCREEN_WIDTH * 0.2 - MeasureText("Recarga", 30) / 2, GetScreenHeight() - 430, 30, FADE);

    DrawTextureEx(power_2, (Vector2) { (SCREEN_WIDTH * 0.5) - (weapon_2.width / 1.25), GetScreenHeight() - 520 }, 0, 1.5, FADE);
    DrawText("Dano", SCREEN_WIDTH * 0.5 - MeasureText("Dano", 30) / 2, GetScreenHeight() - 430, 30, FADE);

    DrawTextureEx(power_3, (Vector2) { (SCREEN_WIDTH * 0.8) - (weapon_3.width / 1.25), GetScreenHeight() - 520 }, 0, 1.5, FADE);
    DrawText("Tamanho", SCREEN_WIDTH * 0.8 - MeasureText("Tamanho", 30) / 2, GetScreenHeight() - 430, 30, FADE);
    
    DrawText("Controles", SCREEN_WIDTH * 0.5 - MeasureText("Controles", 40) / 2, GetScreenHeight() - 350, 40, FADE);
    
    DrawTextureEx(keyboard_up, (Vector2) { SCREEN_WIDTH * 0.5 - (keyboard_up.width / 2) - 16, GetScreenHeight() - 280 }, 0, 4, FADE);
    DrawTextureEx(keyboard_down, (Vector2) { SCREEN_WIDTH * 0.5 - (keyboard_up.width / 2) - 16, GetScreenHeight() - 210 }, 0, 4, FADE);
    DrawTextureEx(keyboard_left, (Vector2) { SCREEN_WIDTH * 0.5 - (keyboard_left.width / 2) - 84, GetScreenHeight() - 210 }, 0, 4, FADE);
    DrawTextureEx(keyboard_right, (Vector2) { SCREEN_WIDTH * 0.5 - (keyboard_right.width / 2) + 52, GetScreenHeight() - 210 }, 0, 4, FADE);
    DrawText("Movimento", SCREEN_WIDTH * 0.5 - MeasureText("Movimento", 30) / 2, GetScreenHeight() - 130, 30, FADE);

    DrawTextureEx(keyboard_esc, (Vector2) { SCREEN_WIDTH * 0.25 - (keyboard_esc.width / 2) - 92, GetScreenHeight() - 210 }, 0, 4, FADE);
    DrawText("Sair", SCREEN_WIDTH * 0.2 - MeasureText("Sair", 30) / 2 - 16, GetScreenHeight() - 130, 30, FADE);

    DrawTextureEx(keyboard_p, (Vector2) { SCREEN_WIDTH * 0.75 - (keyboard_p.width / 2) + 52, GetScreenHeight() - 210 }, 0, 4, FADE);
    DrawText("Pausar", SCREEN_WIDTH * 0.75 - MeasureText("Pausar", 30) / 2 + 72, GetScreenHeight() - 130, 30, FADE);


    DrawText("Pressione enter para continuar...", SCREEN_WIDTH * 0.5 - MeasureText("Pressione enter para continuar", 30) / 2, GetScreenHeight() - 50, 30, Fade(WHITE, GetAlpha()*tutorial_transition_alpha));

    
    EndDrawing();
}


void LoadTutorialTextures() {
    tutorial.texture = LoadTexture("menubg.png");

    weapon_1 = LoadTexture("powerups/pulse.png");
    weapon_2 = LoadTexture("powerups/photon.png");
    weapon_3 = LoadTexture("powerups/shotgun.png");

    power_1 = LoadTexture("powerups/speed.png");
    power_2 = LoadTexture("powerups/damage.png");
    power_3 = LoadTexture("powerups/size.png");

    keyboard_up = LoadTexture("keyboard/arrow_up.png");
    keyboard_down = LoadTexture("keyboard/arrow_down.png");
    keyboard_left = LoadTexture("keyboard/arrow_left.png");
    keyboard_right = LoadTexture("keyboard/arrow_right.png");

    keyboard_esc = LoadTexture("keyboard/key_esc.png");
    keyboard_p = LoadTexture("keyboard/key_p.png");
}

void UnloadTutorialTextures() {
    UnloadTexture(tutorial.texture);

    UnloadTexture(weapon_1);
    UnloadTexture(weapon_2);
    UnloadTexture(weapon_3);

    UnloadTexture(power_1);
    UnloadTexture(power_2);
    UnloadTexture(power_3);
    
    UnloadTexture(keyboard_up);
    UnloadTexture(keyboard_down);
    UnloadTexture(keyboard_left);
    UnloadTexture(keyboard_right);

    UnloadTexture(keyboard_esc);
    UnloadTexture(keyboard_p);
}