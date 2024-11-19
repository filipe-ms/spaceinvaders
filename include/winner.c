#include "winner.h"
#include "scene_manager.h"
#include "raylib.h"
#include "select_ship.h"

static bool returnToMenu = false;

void InitWinner () {
	returnToMenu = false;
}

void UpdateWinner() {
	if (IsKeyPressed(KEY_ENTER)) {
		returnToMenu = true;
	}

	if (returnToMenu) {
		ChangeScene(ENTER_NAME);
	}
}

void DrawWinner() {
	BeginDrawing();
	ClearBackground(BLACK);
	DrawSelectMenuBackground();
	DrawText("Parabens, voce venceu!", GetScreenWidth() / 2 - MeasureText("Parabéns, você venceu!", 40) / 2, GetScreenHeight() / 2 - 40, 40, WHITE);
	DrawText("Pressione ENTER para voltar ao menu", GetScreenWidth() / 2 - MeasureText("Pressione ENTER para voltar ao menu", 20) / 2, GetScreenHeight() / 2 + 20, 20, GRAY);
	EndDrawing();
}
