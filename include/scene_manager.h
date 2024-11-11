//--------------------------------------------------------------
//
//                      scene_manager.h
// 
//--------------------------------------------------------------
// 
// 
//--------------------------------------------------------------

#pragma once

#include "raylib.h"

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

typedef enum {
    VOID = 0,
    START,
    SELECT_SHIP,
    TUTORIAL,
    GAME,
    WINNER,
    GAME_OVER,
    ENTER_NAME,
    RANKING,
    EXIT
} Scene;

void InitSceneManager(Scene scene);
void ChangeScene(Scene scene);
void ChangeSceneArgs(Scene scene, int id);
void LoopScene(void);

#endif // SCENE_MANAGER_H