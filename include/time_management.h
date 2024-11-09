// time_management.h

#pragma once

#include "raylib.h"

#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

const float update_time_s = 1.0 / 60.0;
static float elapsed_time_s = 0;
float game_loop_remains_s = 0;
float update_delta_s = 0;
float updateStart = 0;

void UpdateTime() {
    update_delta_s = GetTime() - updateStart;
    game_loop_remains_s += update_delta_s;
    updateStart = GetTime();
}

float GetElapsedTime() {
    return game_loop_remains_s;
}

void GameLoopUpdate() {
    game_loop_remains_s -= update_time_s;
}

float GetFrameUpdateTime() {
    return update_time_s;
}
float GetUpdatedDelta() {
    return update_delta_s;
}

bool IsItTimeToDraw() {
    return game_loop_remains_s >= update_time_s;
}

void InitUpdateStart() {
    updateStart = GetTime();
}

#endif // TIME_MANAGEMENT_H