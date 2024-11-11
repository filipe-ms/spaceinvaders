// tutorial.h

#pragma once

#include "raylib.h"
#include "game_constants.h"

#ifndef TUTORIAL_H
#define TUTORIAL_H

void InitTutorial(int ship_id);
void UpdateTutorial(void);
void DrawTutorial(void);
void LoadTutorialTextures(void);
void UnloadTutorialTextures(void);

#endif // TUTORIAL_H