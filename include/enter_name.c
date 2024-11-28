#include "enter_name.h"
#include "ranking.h"
#include "raylib.h"
#include <string.h>
#include "game.h"
#include "scene_manager.h"
#include "select_ship.h"
#include "winner.h"

#define MAX_NAME_LENGTH 20

static char playerName[MAX_NAME_LENGTH + 1] = "";  
static int charIndex = 0;                          
char message[50];
bool message_flag = false;


//test
void InitEnterName(void) {
    memset(playerName, 0, sizeof(playerName));  
    charIndex = 0;
    bool message_flag = false;
}

void UpdateEnterName(void) {
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (charIndex < MAX_NAME_LENGTH - 1)) {
            playerName[charIndex] = (char)key;
            charIndex++;
            playerName[charIndex] = '\0';
        }
        message_flag = false;
        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) && charIndex > 0) {
        charIndex--;
        playerName[charIndex] = '\0';
        message_flag = false;
    }

    if (IsKeyPressed(KEY_ENTER)) {
        if (charIndex == 0) {
            message_flag = true;
            strcpy(message, "O nome nao pode estar vazio");
        }
        else {
            AddToRanking(playerName, GetScore());
            ChangeScene(RANKING);
        }
    }
}


void DrawEnterName(void) {
	BeginDrawing();
    ClearBackground(BLACK);
    DrawSelectMenuBackground();
    DrawText("Escreva seu nome:", 100, 100, 30, WHITE);
    DrawText(playerName, 100, 150, 30, WHITE);  // Exibe o nome do jogador conforme ele digita
    if (message_flag) {
		DrawText(message, 100, 200, 30, RED);
    }
	EndDrawing();
}
