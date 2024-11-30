//--------------------------------------------------------------
//
//                      scene_manager.h
// 
//--------------------------------------------------------------
// 
// 
//--------------------------------------------------------------

#pragma once

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "raylib.h"

typedef enum {
    VOID,
    START,
    SELECT_SHIP,
    TUTORIAL,
    GAME,
    WINNER,
    GAME_OVER,
    ENTER_NAME,
    RANKING,
    CREDITS,
    EXIT
} Scene;

void InitSceneManager(Scene scene);
void ChangeScene(Scene scene);
void ChangeSceneArgs(Scene scene, int id);
void LoopScene(void);

#endif // SCENE_MANAGER_H