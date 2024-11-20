// tutorial.h

#pragma once

#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "raylib.h"

void InitTutorial(int ship_id);
void UpdateTutorial(void);
void DrawTutorial(void);
void LoadTutorialTextures(void);
void UnloadTutorialTextures(void);

#endif // TUTORIAL_H