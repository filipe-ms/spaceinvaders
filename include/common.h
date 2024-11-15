//--------------------------------------------------------------
//
//                          common.h
// 
//--------------------------------------------------------------
// 
//      Utilizado para objetos, variáveis e afins 
//            comuns a várias partes do jogo.
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

// Número de inimigos
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

//--------------------------------------------------------------
//
//                          LIST
// 
//--------------------------------------------------------------

typedef struct List {
	void* data;
	struct List* next;
} List;

void AddFirst(List** head, void* value);
void AddLast(List** head, void* value);
void RemoveFirst(List** head);
void RemoveLast(List** head);
void RemoveAll(List** head);

#endif // COMMON_H
