// background_manager.c

#include "background_manager.h"

void InitBackground(Background* background) {
    background->position_y = -1200;
    background->color = (Color){ 255, 255, 255, 170 };
    background->alpha = 0;
}

void DrawBackground(Background* background) {
    DrawTexture(background->texture, background->position_x, background->position_y, Fade(background->color, background->alpha));
    DrawTexture(background->texture, background->position_x, background->position_y - 2400, Fade(background->color, background->alpha));
}

void UpdateBackground(Background* background) {
    if (background->alpha < 0.7) background->alpha += 0.2f * GetFrameTime();
    background->position_y = fmod(background->position_y + 75 * GetFrameTime(), 2400);
}

void LoadBackgroundTexture(Background* background) {
    background->texture = LoadTexture("purplebg.png");
}

void UnloadBackgroundTexture(Background* background) {
    UnloadTexture(background->texture);
}
