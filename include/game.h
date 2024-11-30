//--------------------------------------------------------------
//
//							game.h
// 
//--------------------------------------------------------------
// 
//			Toda a l�gica de jogo acontece aqui.
// 
//--------------------------------------------------------------


#pragma once

#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "weapon.h"

void InitGame(int ship_id);         // Initialize game
void UpdateGame(void);       // Update game (one frame)
void DrawGame(void);         // Draw game (one frame)

// LOAD | UNLOAD
void LoadGameTextures(void);
void UnloadGameTextures(void);

#endif // GAME_H