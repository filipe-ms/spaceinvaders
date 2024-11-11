// draw_object.c

#include "draw_object.h"
#include "player.h"
#include "string.h"

// Texturas
Texture ships;
Texture thrusters;

// Fun��es

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

    DrawTexturePro(ships, orion_sprite, orion->destination, (Vector2) { 9, 10 }, 0, Fade(orion->color, orion->alpha));
    DrawTexturePro(thrusters, orion_thruster, thruster_destination, (Vector2) { 9, 10 }, 0, Fade(orion->color, orion->alpha));
}

//--------------------------------------------------------------
//
//                      Aurea
// 
//--------------------------------------------------------------

/* Usar CENTER, LEFT ou RIGHT para direction. */
void DrawAurea(Aurea* aurea) {
    Rectangle aurea_sprite = { 8, 8, 8, 8 };

    Rectangle aurea_thruster_1 = { 64, 0, 8, 8 };
    Rectangle aurea_thruster_2 = { 40, 0, 8, 8 };

    Rectangle thruster_1_destination = aurea->destination;
    Rectangle thruster_2_destination = aurea->destination;

    thruster_1_destination.y += 64;
    thruster_1_destination.x += 16;

    thruster_2_destination.y += 64;
    thruster_2_destination.x -= 24;

    switch (aurea->direction) {
    case LEFT:
        aurea_sprite = (Rectangle){ 0, 8, 8, 8 };
        thruster_1_destination.x -= 16;
        thruster_2_destination.x -= 8;
        break;

    case RIGHT:
        thruster_1_destination.x += 8;
        thruster_2_destination.x += 16;
        aurea_sprite = (Rectangle){ 16, 8, 8, 8 };
        break;
    }

    switch (aurea->thruster_cycle) {
    case 1:
        aurea_thruster_1 = (Rectangle){ 40, 0, 8, 8 };
        aurea_thruster_2 = (Rectangle){ 56, 0, 8, 8 };
        break;
    case 2:
        aurea_thruster_1 = (Rectangle){ 48, 0, 8, 8 };
        aurea_thruster_2 = (Rectangle){ 64, 0, 8, 8 };
        break;
    case 3:
        aurea_thruster_1 = (Rectangle){ 56, 0, 8, 8 };
        aurea_thruster_2 = (Rectangle){ 48, 0, 8, 8 };
        break;
    }

    DrawTexturePro(ships, aurea_sprite, aurea->destination, (Vector2) { 9, 10 }, 0, Fade(aurea->color, aurea->alpha));
    DrawTexturePro(thrusters, aurea_thruster_1, thruster_1_destination, (Vector2) { 9, 10 }, 0, Fade(aurea->color, aurea->alpha));
    DrawTexturePro(thrusters, aurea_thruster_2, thruster_2_destination, (Vector2) { 9, 10 }, 0, Fade(aurea->color, aurea->alpha));
}

//--------------------------------------------------------------
//
//                      GEN�RICOS
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