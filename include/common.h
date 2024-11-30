//--------------------------------------------------------------
//
//                          common.h
// 
//--------------------------------------------------------------
// 
//      Utilizado para objetos, vari�veis e afins 
//            comuns a v�rias partes do jogo.
// 
//--------------------------------------------------------------

#pragma once

#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"

//--------------------------------------------------------------
//
//                          DEFINES
// 
//--------------------------------------------------------------


// Tamanho da tela
#define SCREEN_WIDTH 640   // Largura
#define SCREEN_HEIGHT 960  // Altura

// N�mero de inimigos
#define MAX_ENEMY_NUMBER 100


//--------------------------------------------------------------
//
//                          OBJECTS
// 
//--------------------------------------------------------------

typedef struct Background {
    Texture texture;
    float position_x;
    float position_y;
    Color color;
    float alpha;
} Background;

#endif // COMMON_H
