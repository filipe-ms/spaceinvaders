#pragma once

#ifndef BOSS_H
#define BOSS_H

#include "raylib.h"
#include "player.h"
#include "weapon.h"

typedef struct Boss
{
	int id;
	bool active;

	float max_hp;
	float cur_hp;
	float alpha;

	Rectangle texture_pos;
	
	Rectangle source;
	Rectangle position;

	Vector2 offset;
	Vector2 speed;
	Color color;

} Boss;


void InitBoss();
void UpdateBoss();
void DrawBoss();
void LoadBossTextures();
void UnloadBossTextures();
bool CheckBossCollisionWithPlayer(Player player);
bool IsBossActive(void);
bool IsBossDead(void);
void CheckBossHit(Shoot* shoot);

#endif // BOSS_H
