//--------------------------------------------------------------
//
//                      draw_object.h
// 
//--------------------------------------------------------------
// 
// Esse header serve para desenhar os assets.
// Separei dos outros lugares pra facilitar o desenho.
// 
//--------------------------------------------------------------

#pragma once

#include "raylib.h"

#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

#define CENTER 0
#define LEFT 1
#define RIGHT 2

#define ORION 0

// Espec�ficos

typedef struct Orion {
    Rectangle destination;  // O local em que vai ser desenhado
    int direction;        // Para que lado est� andando
    int thruster_cycle;     // Em que ciclo o thsuter est�
    Color color;            // Cor
    float alpha;            // Transpar�ncia
} Orion;

void DrawOrion(Orion *orion);

// Gen�ricos

typedef struct ObjectPro {
    Texture texture;        // A textura
    Rectangle position;     // A posi��o na sheet
    Rectangle destination;  // O local em que vai ser desenhado
    Vector2 offset;         // Se houver offset
    float rotation;         // Rota��o
    Color color;            // Cor
    float alpha;            // Transpar�ncia
} ObjectPro;

void DrawObjectPro(ObjectPro *object);

void LoadObjectTextures(void);
void UnloadObjectTextures(void);



#endif // DRAW_OBJECT_H