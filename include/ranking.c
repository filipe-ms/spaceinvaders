#include "ranking.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "scene_manager.h"

static RankingEntry entries[MAX_ENTRIES];
static int playerCount = 0;

void InitRanking() {
    // Inicializa o ranking e tenta carregar do arquivo
    for (int i = 0; i < MAX_ENTRIES; i++) {
        strcpy(entries[i].name, "");
        entries[i].score = -1;
    }
    playerCount = 0;
    LoadRanking();  // Carrega o ranking salvo
}

void AddToRanking(const char* name, int score) {
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

void SaveRanking() {
    FILE* file = fopen("ranking.txt", "w");
    if (file) {
        fprintf(file, "%d\n", playerCount);
        for (int i = 0; i < playerCount; i++) {
            fprintf(file, "%s %d\n", entries[i].name, entries[i].score);
        }
        fclose(file);
    }
}

void LoadRanking() {
    FILE* file = fopen("ranking.txt", "r");
    if (file) {
        fscanf(file, "%d", &playerCount);
        for (int i = 0; i < playerCount; i++) {
            fscanf(file, "%s %d", entries[i].name, &entries[i].score);
        }
        fclose(file);
    }
}

void UpdateRanking() {
    if (IsKeyPressed(KEY_ENTER)) {
        ChangeScene(START);
    }
}

void DrawRanking(int posX, int posY) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Best Scores", posX, posY, 30, WHITE);

    int displayedEntries = 0;
    for (int i = 0; i < MAX_ENTRIES && displayedEntries < playerCount; i++) {
        if (entries[i].score >= 0 && strlen(entries[i].name) > 0) {
            char entryText[50];
            snprintf(entryText, sizeof(entryText), "%d. %s - %d (Score)", displayedEntries + 1, entries[i].name, entries[i].score);
            DrawText(entryText, posX, posY + (displayedEntries + 1) * 30, 20, WHITE);
            displayedEntries++;
        }
    }
    EndDrawing();
}
