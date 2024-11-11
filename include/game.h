#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"

void InitGame(void);         // Initialize game
void UpdateGame(void);       // Update game (one frame)
void DrawGame(void);         // Draw game (one frame)

// LOAD | UNLOAD
void LoadGameTextures(void);
void UnloadGameTextures(void);

#endif // GAME_H