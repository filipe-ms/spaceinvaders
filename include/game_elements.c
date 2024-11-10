// game_elements.c

#include "game_elements.h"

void InitBackground(struct Background* background) {
    background->position_y = -1200;
    background->color = (Color){ 255, 255, 255, 170 };
    background->alpha = 0;
}

void UpdateBackground(struct Background* background) {
    if (background->alpha < 0.7) background->alpha += 0.2f * GetFrameTime();
    background->position_y = fmod(background->position_y + 75 * GetFrameTime(), 2400);
}

void DrawBackground(struct Background* background) {
    DrawTexture(background->texture, 0, background->position_y, Fade(background->color, background->alpha));
    DrawTexture(background->texture, 0, background->position_y - 2400, Fade(background->color, background->alpha));
}

void LoadBackgroundTexture(struct Background* background) {
    background->texture = LoadTexture("purplebg.png");
}

void UnloadBackgroundTexture(struct Background* background) {
    UnloadTexture(background->texture);
}
