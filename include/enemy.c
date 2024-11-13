#include "enemy.h"
#include "game_constants.h"

Rectangle enemy_rectangles[5] = {
    { 48, 8, 8, 8 },
    { 32, 24, 8, 8 },
    { 48, 24, 8, 8 },
    { 32, 8, 8, 8 },
    { 16, 8, 8, 8 }
};

Texture enemy_texture;
Vector2 enemy_vect = { 0, 0 };

void InitEnemies(Enemy *enemy) {
    for (int i = 0; i < 50; i++)
    {
		enemy[i].id = GetRandomValue(0, 4);

        enemy[i].position.width = 48;
        enemy[i].position.height = 48;
        enemy[i].position.x = (float)GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH + 1000);
        enemy[i].position.y = (float)GetRandomValue(0, (int)(SCREEN_HEIGHT - enemy[i].position.height));
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 120;
        enemy[i].active = false;
        enemy[i].color = GRAY;
        enemy[i].hp = 3.0f;
		enemy[i].exp = 1.0f;
    }
}

void SpawnEnemies(Enemy *enemy, int amount, int id) {
	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < 50; j++){
			if (enemy[j].active) continue;

			if (!enemy[j].active) {
                enemy[j].active = true;
                enemy[j].position.x = (float)GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH + 1000);
                enemy[j].position.y = (float)GetRandomValue(0, (int)(SCREEN_HEIGHT - enemy[j].position.height));
                enemy[j].id = id;
                enemy[j].hp = 3;
				break;
			}
		}
	}
}

void UpdateEnemies(Enemy *enemy) {
    for (int i = 0; i < 50; i++)
    {
        if (!enemy[i].active) continue;
        
        enemy[i].position.y += enemy[i].speed.y * GetFrameTime();

        if (enemy[i].position.y > SCREEN_HEIGHT)
        {
            enemy[i].position.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(enemy[i].position.width));
            enemy[i].position.y = (float)(GetRandomValue(-200, -400));
        }
    }
}

void DrawEnemies(Enemy *enemy) {
    for (int i = 0; i < 50; i++)
    {
        if (enemy[i].active) {
			DrawRectangleRec(enemy[i].position, enemy[i].color);
            DrawTexturePro(enemy_texture, enemy_rectangles[enemy->id], enemy[i].position, enemy_vect, 0, enemy[i].color);
        }
    }
}

bool CheckEnemyCollisionWithPlayer(Player player, Enemy *enemy) {
    for (int i = 0; i < 50; i++) {
		if (!enemy[i].active) continue;
        if (CheckCollisionRecs(player.position, enemy[i].position)) {
            return true;
        }
    }
    return false;
}

void LoadEnemyTextures() {
    enemy_texture = LoadTexture("ships.png");
}

void UnloadEnemyTextures() {
    UnloadTexture(enemy_texture);
}

/*
MOVIMENTO ALEATORIO

void InitEnemy(Enemy* enemy) {
    for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
        enemy->position.width = 48;
        enemy->position.height = 48;
        enemy->position.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)enemy->position.width);
        enemy->position.y = (float)GetRandomValue(-200, -400);
        enemy->speed.x = 0;
        enemy->speed.y = (float)GetRandomValue(50, 150);
        enemy->active = true;
        enemy->color = GRAY;
        enemy->hp = 3.0f;
        enemy->ProLado = (float)GetRandomValue(1, 5); // tempo pra movimentar pro lado
    }
}
void InitEnemies(Enemy enemy[]) { // funcao inutiu tirar dps
    for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
        InitEnemy(&enemy[i]);
    }
}

void EnemyMovement(Enemy* enemy) {
    if (!enemy->active) return;

    float booster = GetRandomValue(1, 10); // boosrter pra aumentar velocidade aleatoriamente

    enemy->position.y += enemy->speed.y * GetFrameTime();

    enemy->position.x += enemy->speed.x * GetFrameTime() * booster; // aumentando so pros lados pq pra frente ficou estranho

    if (enemy->position.x < 0) {
        enemy->position.x = 0;
        enemy->speed.x *= -1; // inverte se chega em uma ponta
    }
    else if (enemy->position.x > SCREEN_WIDTH - enemy->position.width) {
        enemy->position.x = SCREEN_WIDTH - enemy->position.width;
        enemy->speed.x *= -1; // invertendo pra chegar na outra
    }

    enemy->ProLado -= GetFrameTime();

    if (enemy->ProLado <= 0) {// quando tempo esgotar escolher outro aleatorio
        enemy->speed.x = (float)GetRandomValue(-50, 50);
        enemy->ProLado = (float)GetRandomValue(1, 5);
    }
}

void UpdateEnemies(Enemy enemy[], int activeEnemies) {
    for (int i = 0; i < activeEnemies; i++) {
        EnemyMovement(&enemy[i]);

        // Reseta a posição do inimigo se ele passar da borda inferior da tela
        if (enemy[i].position.y > SCREEN_HEIGHT) {
            enemy[i].position.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(enemy[i].position.width));
            enemy[i].position.y = (float)GetRandomValue(-200, -400);
            enemy[i].speed.y = (float)GetRandomValue(50, 150); // Velocidade vertical randômica para nova queda
        }
    }
}*/