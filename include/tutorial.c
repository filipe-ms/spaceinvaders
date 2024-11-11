// tutorial.c


#include "select_ship.h"
#include "math.h"
#include "player.h"
#include "commons.h"
#include "scene_manager.h"

Background tutorial;
int id;

void InitTutorial(int ship_id) {
    id = ship_id;
    tutorial.position_y = 0;
    tutorial.position_x = 0;
    tutorial.color = WHITE;
    tutorial.alpha = 1;
}

void UpdateTutorial(void) {
    if (IsKeyPressed(KEY_ENTER)) {
        ChangeSceneArgs(GAME, id);
    }
}

void DrawTutorial() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(tutorial.texture, (int)(tutorial.position_x), (int)(tutorial.position_y), Fade(tutorial.color, tutorial.alpha));
    EndDrawing();
}


void LoadTutorialTextures() {
    tutorial.texture = LoadTexture("tutorial.png");
}

void UnloadTutorialTextures() {
    UnloadTexture(tutorial.texture);
}