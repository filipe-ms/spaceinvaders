#include "enemy.h"
#include "common.h"

Rectangle enemy_rectangles[5] = {
    { 32, 0, 8, 8 },
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
        enemy[i].speed.x = 0;
        enemy[i].speed.y = 120;
        enemy[i].active = false;
        enemy[i].color = WHITE;
        enemy[i].hp = 3.0f;
		enemy[i].exp = 10.0f;
        enemy[i].move_time = 0;
		enemy[i].action_flag = false;
    }
}
/* spawn paredão

*/

void SpawnEnemies(Enemy *enemy, int amount, int id) {
	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < 50; j++){
			if (enemy[j].active) continue;

            enemy[j].active = true;
            enemy[j].position.x = (float)GetRandomValue(0, SCREEN_WIDTH - enemy[j].position.width);
            enemy[j].position.y = (float)GetRandomValue(-200, 0);
            enemy[j].id = id;
            enemy[j].hp = 3;
            break;
		}
	}
}

void SpawnRandomEnemies(Enemy* enemy, int amount) {
    for (int i = 0; i < amount; i++)
    {
        for (int j = 0; j < 50; j++) {
            if (enemy[j].active) continue;
            enemy[j].active = true;
            enemy[j].position.x = (float)GetRandomValue(0, SCREEN_WIDTH - enemy[j].position.width);
            enemy[j].position.y = (float)GetRandomValue(-200, 0);
            enemy[j].id = GetRandomValue(0, 3);
            enemy[j].hp = 3;
            break;
        }
    }
}

void EnemyParedao(Enemy* enemy) {
    //float amplitude = (float)GetRandomValue(0, 6);
    //float velocidade = (float)GetRandomValue(1.6, 2.4);
    if(enemy->action_flag == false) {
        enemy->position.x = (float)GetRandomValue(SCREEN_WIDTH, SCREEN_WIDTH + 1000);
        enemy->position.y = (float)GetRandomValue(0, (int)(SCREEN_HEIGHT-150));
		enemy->action_flag = true;
    }

    static float f = 0;
    
    float amplitude = 6;
    float velocidade = 16;

    if (enemy->speed.x == 0) enemy->speed.x = velocidade;

    if (enemy->active) {
        //enemy->position.y += enemy->speed.y * GetFrameTime();
        enemy->position.x += amplitude * sin(f) * enemy->speed.x * GetFrameTime();
    }

    f += GetFrameTime();

    if (enemy->position.y > SCREEN_HEIGHT)
    {
        enemy->position.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(enemy->position.width));
        enemy->position.y = (float)(GetRandomValue(-200, -400));
		enemy->action_flag = false;
    }
}

void EnemyLeigo(Enemy* enemy) {
    if (!enemy->active) return;
	enemy->position.y += enemy->speed.y * GetFrameTime();

    if (enemy->position.y > SCREEN_HEIGHT)
    {
        enemy->position.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(enemy->position.width));
        enemy->position.y = (float)(GetRandomValue(-200, -400));
    }
}

void EnemyZigZag(Enemy* enemy) {
    if (!enemy->active) return;

    if (enemy->move_time <= 0) {
        enemy->move_time = (float)GetRandomValue(1, 2);
		int random_speed = GetRandomValue(0, 1);
		if (random_speed == 0) enemy->speed.x = 100;
		else enemy->speed.x = -100;
    }
    
    float boost = GetRandomValue(1, 5);

    enemy->position.y += enemy->speed.y * GetFrameTime();
    enemy->position.x += enemy->speed.x * boost * GetFrameTime();

    enemy->move_time -= GetFrameTime();

    if (enemy->position.y > SCREEN_HEIGHT)
    {
        enemy->position.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(enemy->position.width));
        enemy->position.y = (float)(GetRandomValue(-200, -400));
    }
}

void EnemyBooster(Enemy* enemy, Player* player) {
    if (!enemy->active) return;

    if (enemy->position.y < 100) {
        enemy->position.y += 100 * GetFrameTime();
    }
    else {
        if (!enemy->action_flag) {
            enemy->move_time = 2.0f;
            enemy->action_flag = true;
        }

        if (enemy->move_time > 0) {
            enemy->move_time -= GetFrameTime();

            if (enemy->position.x < player->position.x) {
                enemy->position.x += 100 * GetFrameTime();
                if (enemy->position.x > player->position.x) {
                    enemy->position.x = player->position.x;
                }
            }
            else if (enemy->position.x > player->position.x) {
                enemy->position.x -= 100 * GetFrameTime();
                if (enemy->position.x < player->position.x) {
                    enemy->position.x = player->position.x;
                }
            }
        }
        else {
            enemy->position.y += 1000 * GetFrameTime();
        }
        if (enemy->position.y > SCREEN_HEIGHT) {
            enemy->action_flag = false;
            enemy->position.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(enemy->position.width));
            enemy->position.y = (float)(GetRandomValue(-200, -400));
        }
    }
}


void UpdateEnemies(Enemy *enemy, Player *player) {
    for (int i = 0; i < 50; i++)
    {
        if (!enemy[i].active) continue;

        switch (enemy[i].id) {
        case 0:
            EnemyLeigo(&enemy[i]);
            break;
        case 1:
            EnemyZigZag(&enemy[i]);
			break;

        case 2:
			EnemyBooster(&enemy[i], player);
            break;

        case 3:
            EnemyParedao(&enemy[i]);
            break;
        }



        if(enemy[i].position.x < 0 + enemy[i].position.width) {
			enemy[i].position.x = 0 + enemy[i].position.width;
            enemy[i].speed.x *= -1;
		} else if (enemy[i].position.x > SCREEN_WIDTH - enemy[i].position.width/2) {
			enemy[i].position.x = SCREEN_WIDTH - enemy[i].position.width/2;
            enemy[i].speed.x *= -1;
        }
    }
}

void DrawEnemies(Enemy *enemy) {
    for (int i = 0; i < 50; i++)
    {
        if (enemy[i].active) {
            DrawTexturePro(enemy_texture, enemy_rectangles[enemy[i].id], enemy[i].position, enemy_vect, 0, enemy[i].color);
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