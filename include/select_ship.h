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

typedef struct SelectMenuShip {
    Texture texture;
    Rectangle sprite_location;
    Rectangle sprite_destination;
    Color color;
    float alpha;
} SelectMenuShip;

void InitSelectMenu(void);
void UpdateShipSelectMenu(void);
void DrawSelectMenu(void);
void LoadSelectMenuTextures(void);
void UnloadSelectMenuTextures(void);

#endif // SELECT_SHIP_H
