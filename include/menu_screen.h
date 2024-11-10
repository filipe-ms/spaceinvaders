// menu_screen.h

#pragma once

#include "raylib.h"
#include "game_constants.h"

#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

typedef enum {
    MENU_OPTION_START,
    MENU_OPTION_RANKING,
    MENU_OPTION_EXIT,
    MENU_OPTION_COUNT
} MenuOption;

typedef struct MenuBackground {
    Texture texture;
    Color color;
    float alpha;
    float y_offset;

} MenuBackground;

void InitMenu();
void UpdateMenu(GameScreen* game_screen);
void DrawMenu();
void LoadMenuBackgroundTexture(void);
void UnloadMenuBackgroundTexture(void);
void SetTransitionFalse(void);

bool MenuTransition();

#endif // MENU_SCREEN_H
