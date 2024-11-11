// draw_object.c

#include "draw_object.h"
#include "player.h"
#include "string.h"

// Texturas
Texture ships;
Texture thrusters;

// Funções

//--------------------------------------------------------------
//
//                      ORION
// 
//--------------------------------------------------------------

/* Usar CENTER, LEFT ou RIGHT para direction. */
void DrawOrion(Orion* orion) {
    Rectangle orion_sprite = { 8, 0, 8, 8 };
    Rectangle orion_thruster = { 64, 8, 8, 8 };
    Rectangle thruster_destination = orion->destination;
    thruster_destination.y += 56;

    switch(orion->direction) {
    case LEFT:
        orion_sprite = (Rectangle){ 0, 0, 8, 8 };
        thruster_destination.x -= 8;
        break;
    
    case RIGHT:
        thruster_destination.x += 8;
        orion_sprite = (Rectangle){ 16, 0, 8, 8 };
        break;
    }

    switch (orion->thruster_cycle) {
    case 1:
        orion_thruster = (Rectangle){ 40, 8, 8, 8 };
        break;
    case 2:
        orion_thruster = (Rectangle){ 48, 8, 8, 8 };
        break;
    case 3:
        orion_thruster = (Rectangle){ 56, 8, 8, 8 };
        break;
    }

    DrawTexturePro(ships, orion_sprite, orion->destination, (Vector2){ 0, 0 }, 0, Fade(orion->color, orion->alpha));
    DrawTexturePro(thrusters, orion_thruster, thruster_destination, (Vector2){ 0, 0 }, 0, Fade(orion->color, orion->alpha));
}

//--------------------------------------------------------------
//
//                      GENÉRICOS
// 
//--------------------------------------------------------------



void DrawObjectPro(ObjectPro* object) {
    DrawTexturePro(object->texture, object->position, object->destination, object->offset, object->rotation, Fade(object->color, object->alpha));
}

void LoadObjectTextures(void) {
    ships = LoadTexture("ships.png");
    thrusters = LoadTexture("playerassets.png");
}

void UnloadObjectTextures(void) {
    UnloadTexture(ships);
    UnloadTexture(thrusters);
}