#include "ranking.h"
#include "raylib.h"
#include "scene_manager.h"
#include "select_ship.h"
#include "common.h"

#include <stdio.h>
#include <string.h>

RankingEntry entries[MAX_ENTRIES];
int playerCount = 0;
bool enter_transition = true;
bool leave_transition = false;
float rec_alpha = 1.0f;

void LoadRanking(void) {
	FILE* file = fopen("ranking.txt", "r");
	if (file) {
		fscanf(file, "%d", &playerCount);
		for (int i = 0; i < playerCount; i++) {
			fscanf(file, "%s %d", entries[i].name, &entries[i].score);
		}
		fclose(file);
	}
}

void InitRanking() {
    playerCount = 0;
    enter_transition = true;
    leave_transition = false;
    rec_alpha = 0.0f;

    // Inicializa o ranking e tenta carregar do arquivo
    for (int i = 0; i < MAX_ENTRIES; i++) {
        strcpy(entries[i].name, "");
        entries[i].score = -1;
    }
    playerCount = 0;
    LoadRanking();  // Carrega o ranking salvo
}

void SaveRanking(void) {
	FILE* file = fopen("ranking.txt", "w");
	if (file) {
		fprintf(file, "%d\n", playerCount);
		for (int i = 0; i < playerCount; i++) {
			fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
		}
		fclose(file);
	}
}

void AddToRanking(const char* name, int score) {
    LoadRanking();

	RankingEntry newEntry;
	strncpy(newEntry.name, name, MAX_NAME_LENGTH - 1);
	newEntry.name[MAX_NAME_LENGTH - 1] = '\0';
	newEntry.score = score;

	// Insere o novo score na posição correta
	for (int i = 0; i < MAX_ENTRIES; i++) {
		if (newEntry.score > entries[i].score || entries[i].score == -1) {
			for (int j = MAX_ENTRIES - 1; j > i; j--) {
				entries[j] = entries[j - 1];
			}
			entries[i] = newEntry;
			if (playerCount < MAX_ENTRIES) playerCount++;
			break;
		}
	}
	SaveRanking();  // Salva o ranking atualizado
}

void UpdateRanking() {
    if (IsKeyPressed(KEY_ENTER)) {
        leave_transition = true;
    }

    if (enter_transition && !leave_transition) {
        rec_alpha -= 0.5f * GetFrameTime();
        if (rec_alpha <= 0) {
            rec_alpha = 0;
            enter_transition = false;
        }
    }

    if (!enter_transition && leave_transition) {
        rec_alpha += 0.5f * GetFrameTime();
        if (rec_alpha >= 1) {
            rec_alpha = 1;
            leave_transition = false;
            ChangeScene(START);
        }
    }
}

void DrawRanking(int posX, int posY) {
    BeginDrawing();
    ClearBackground(BLACK);
	DrawSelectMenuBackground();
    DrawText("Melhores jogadores", posX, posY, 30, WHITE);

    int displayedEntries = 0;
    for (int i = 0; i < MAX_ENTRIES && displayedEntries < playerCount; i++) {
        if (entries[i].score >= 0 && strlen(entries[i].name) > 0) {
            char entryText[50];
            snprintf(entryText, sizeof(entryText), "%d. %s - %d (Score)", displayedEntries + 1, entries[i].name, entries[i].score);
            DrawText(entryText, posX, posY + (displayedEntries + 1) * 30, 20, WHITE);
            displayedEntries++;
        }
    }

    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, rec_alpha));
    EndDrawing();
}
