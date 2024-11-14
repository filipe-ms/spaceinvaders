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

#ifndef DRAW_OBJECT_H
#define DRAW_OBJECT_H

#define CENTER 0
#define LEFT 1
#define RIGHT 2

#define AUREA 0
#define ORION 1
#define NEBULA 2

#include "raylib.h"




// Específicos

// Aurea
typedef struct Aurea {
    Rectangle destination;  // O local em que vai ser desenhado
    int direction;        // Para que lado está andando
    int thruster_cycle;     // Em que ciclo o thruster está
    Color color;            // Cor
    float alpha;            // Transparência
} Aurea;

void DrawAurea(Aurea* aurea);

// Orion
typedef struct Orion {
    Rectangle destination;  // O local em que vai ser desenhado
    int direction;        // Para que lado está andando
    int thruster_cycle;     // Em que ciclo o thruster está
    Color color;            // Cor
    float alpha;            // Transparência
} Orion;

void DrawOrion(Orion *orion);

// Nebula
typedef struct Nebula {
    Rectangle destination;  // O local em que vai ser desenhado
    int direction;        // Para que lado está andando
    int thruster_cycle;     // Em que ciclo o thruster está
    Color color;            // Cor
    float alpha;            // Transparência
} Nebula;

void DrawNebula(Nebula* nebula);

// Genéricos

typedef struct ObjectPro {
    Texture texture;        // A textura
    Rectangle position;     // A posição na sheet
    Rectangle destination;  // O local em que vai ser desenhado
    Vector2 offset;         // Se houver offset
    float rotation;         // Rotação
    Color color;            // Cor
    float alpha;            // Transparência
} ObjectPro;

void DrawObjectPro(ObjectPro *object);

void LoadObjectTextures(void);
void UnloadObjectTextures(void);



#endif // DRAW_OBJECT_H
