// time_management.h

#pragma once

#include "raylib.h"

#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

extern const float update_time_s;
extern float elapsed_time_s;
extern float game_loop_remains_s;
extern float update_delta_s;
extern float updateStart;

void UpdateTime();
float GetElapsedTime();
void GameLoopUpdate();
float GetFrameUpdateTime();
float GetUpdatedDelta();
bool IsItTimeToDraw();
void InitUpdateStart();

#endif // TIME_MANAGEMENT_H
