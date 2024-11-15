#ifndef RANKING_H
#define RANKING_H

#define MAX_ENTRIES 10
#define MAX_NAME_LENGTH 20

typedef struct {
    char name[MAX_NAME_LENGTH + 1];
    int score;
} RankingEntry;

void InitRanking();               // Inicializa o ranking (carrega se já existir)
void AddToRanking(const char* name, int score);  // Adiciona nova entrada e ordena
void LoadRanking();               // Carrega o ranking de um arquivo
void SaveRanking();               // Salva o ranking para um arquivo
void UpdateRanking();             // Atualiza a tela de ranking
void DrawRanking(int posX, int posY); // Desenha a tela de ranking

#endif  // RANKING_H
