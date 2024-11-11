//--------------------------------------------------------------
//
//                          commons.h
// 
//--------------------------------------------------------------
// 
//      Utilizado para objetos comuns a várias partes do jogo.
// 
//--------------------------------------------------------------

#pragma once

#include "raylib.h"

#ifndef BACKGROUND_MANAGER_H
#define BACKGROUND_MANAGER_H

typedef struct Background {
    Texture texture;
    float position_x;
    float position_y;
    Color color;
    float alpha;
} Background;

#endif // BACKGROUND_MANAGER_H
