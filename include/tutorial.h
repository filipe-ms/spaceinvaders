// tutorial.h
/*
#pragma once

#include "raylib.h"
#include "game_constants.h"

#ifndef TUTORIAL_H
#define TUTORIAL_H

typedef struct TutorialImage {
    Texture texture;
    Color color;
    float alpha;
} TutorialImage;

typedef struct TutorialShip {
    Texture texture;
    Rectangle sprite_location;
    Rectangle sprite_destination;
    Color color;
    float alpha;
} SelectMenuShip;

void InitTutorial(void);
void UpdateTutorial(GameScreen* game_screen);
void DrawTutorial(void);
void LoadTutorialTextures(void);
void UnloadTutorialTextures(void);
bool TutorialTransition(void);

#endif // TUTORIAL_H
*/