// select_ship.h

#pragma once

#include "raylib.h"
#include "game_constants.h"

#ifndef SELECT_SHIP_H
#define SELECT_SHIP_H

typedef enum {
    LEFT_SHIP,
    MIDDLE_SHIP,
    RIGHT_SHIP,
    SELECT_MENU_OPTION_COUNT
} SelectMenuOption;

typedef struct SelectMenuBackground {
    Texture texture;
    Color color;
    float alpha;
    float y_offset;

} SelectMenuBackground;

typedef struct SelectMenuShip {
    Texture texture;
    Rectangle sprite_location;
    Rectangle sprite_destination;
    Color color;
    float alpha;
} SelectMenuShip;

void InitSelectMenu(void);
void UpdateSelectMenu(GameScreen* game_screen);
void DrawSelectMenu(void);
void LoadSelectMenuTextures(void);
void UnloadSelectMenuTextures(void);
bool SelectMenuTransition(void);

#endif // SELECT_SHIP_H
