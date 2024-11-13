#include "xp_bar.h"
#include "raylib.h"
#include <math.h>  
#include <stdio.h> 

int exp_count;       // Declaração de xpForLevel como extern
int level;              // Declaração de level como extern
int exp_to_level_up;// Declaração de MaxXPForLevel como extern
int exp_increment_per_level_up = 40;

// Variáveis de desenho
int exp_bar_width = 200;   // largura da barra
int exp_bar_height = 20;   // altura 

float fill_percentage;
int filled_width;
char levelText[20];

void InitExpBar(void) {
    level = 1;        // Inicia o nível no 1
    exp_count = 0;   // Inicia o XP para o nível atual no 0
    exp_to_level_up = 100;
    fill_percentage = 0;
    filled_width = 0;
}

void AddToExp(int experience) {
	exp_count += experience;

    if (exp_count >= exp_to_level_up) {
        level++;
        exp_count = 0;
        exp_to_level_up += exp_increment_per_level_up;
    }
}

void UpdateExpBar(void) {

    // Calcula a porcentagem de preenchimento da barra de XP
    fill_percentage = (float)exp_count / exp_to_level_up;
    filled_width = (int)(fill_percentage * exp_bar_width);
    snprintf(levelText, sizeof(levelText), "Level %d", level);
}

void DrawExpBar(void) {
    // Preenchimento da barrra
    DrawRectangle(50, 860, filled_width, exp_bar_height, Fade(PURPLE, 0.6f));

    // Borda
    DrawRectangleLines(50, 860, exp_bar_width, exp_bar_height, Fade(DARKGRAY, 0.6f));

    //print do nivel
    DrawText(levelText, 50, 860 + exp_bar_height + 20, 30, Fade(WHITE, 0.6f));
}
