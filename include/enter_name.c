#include "enter_name.h"
#include "ranking.h"
#include "raylib.h"
#include <string.h>
#include "game.h"
#include "scene_manager.h"

extern int player_score; // Declaração da variável global


#define MAX_NAME_LENGTH 20

static char playerName[MAX_NAME_LENGTH + 1] = "";  
static int charIndex = 0;                          

//test
void InitEnterName(void) {
    memset(playerName, 0, sizeof(playerName));  
    charIndex = 0;
}

void UpdateEnterName(void) {
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (charIndex < MAX_NAME_LENGTH)) {
            playerName[charIndex] = (char)key;
            charIndex++;
        }
        key = GetCharPressed();
    }

    // Remove o último caractere ao pressionar BACKSPACE
    if (IsKeyPressed(KEY_BACKSPACE) && charIndex > 0) {
        charIndex--;
        playerName[charIndex] = '\0';
    }

    // Avança para a próxima tela ao pressionar ENTER (pode ser o ranking)
    if (IsKeyPressed(KEY_ENTER)) {
        AddToRanking(playerName, player_score);  
        ChangeScene(RANKING);                   
    }
}

void DrawEnterName(void) {
	BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Enter your name:", 100, 100, 30, WHITE);
    DrawText(playerName, 100, 150, 30, WHITE);  // Exibe o nome do jogador conforme ele digita
	EndDrawing();
}
