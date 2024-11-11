// main_menu.h

#pragma once

#include "raylib.h"
#include "game_constants.h"

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

typedef enum {
    MENU_OPTION_START,
    MENU_OPTION_RANKING,
    MENU_OPTION_EXIT,
    MENU_OPTION_COUNT
} MenuOption;

void InitMenu();
void UpdateMenu();
void DrawMenu();
void LoadMenuBackgroundTexture(void);
void UnloadMenuBackgroundTexture(void);

#endif // MAIN_MENU_H
