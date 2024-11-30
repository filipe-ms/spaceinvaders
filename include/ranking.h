#ifndef RANKING_H
#define RANKING_H

#define MAX_ENTRIES 10
#define MAX_NAME_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH + 1];
    int score;
} RankingEntry;

void InitRanking();               // Inicializa o ranking (carrega se já existir)
void UpdateRanking();             // Atualiza a tela de ranking
void DrawRanking(int posX, int posY); // Desenha a tela de ranking
void AddToRanking(const char* name, int score);

#endif  // RANKING_H
