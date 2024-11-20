#include "winner.h"
#include "scene_manager.h"
#include "raylib.h"
#include "select_ship.h"
#include "ranking.h"
#include "stdio.h"

static RankingEntry Score;
static bool returnToMenu = false;

void InitWinner (void) {
	returnToMenu = false;
}
void InitScore(void) {
	Score.score = 0;
}

void AddToScore(int i) {
	Score.score += i;
}

int GetScore(void) {
	return Score.score;
}

void UpdateWinner(void) {
	if (IsKeyPressed(KEY_ENTER)) {
		returnToMenu = true;
		ChangeScene(ENTER_NAME);
	}
}

void DrawWinner(void) {
	BeginDrawing();
	ClearBackground(BLACK);
	DrawSelectMenuBackground();
	DrawText("Parabens, voce venceu!", GetScreenWidth() / 2 - MeasureText("Parabéns, você venceu!", 40) / 2, GetScreenHeight() / 2 - 160, 40, WHITE);
	DrawText("(a fonte nao tem acento)", GetScreenWidth() / 2 - MeasureText("Parabéns, você venceu!", 30) / 2, GetScreenHeight() / 2 - 110, 30, WHITE);
	DrawText("Pressione ENTER para continuar", GetScreenWidth() / 2 - MeasureText("Pressione ENTER para continuar", 24) / 2, GetScreenHeight() / 2 + 20, 24, WHITE);
	EndDrawing();
}
