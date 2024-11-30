#include "xp_bar.h"
#include <math.h>  
#include <stdio.h> 

int exp_count;       // Declara��o de xpForLevel como extern
int level;              // Declara��o de level como extern
int exp_to_level_up;// Declara��o de MaxXPForLevel como extern
int exp_increment_per_level_up = 50;

// Vari�veis de desenho
int exp_bar_width = 200;   // largura da barra
int exp_bar_height = 20;   // altura 

float fill_percentage;
int filled_width;
char levelText[20];

void InitExpBar(void) {
    level = 1;        // Inicia o n�vel no 1
    exp_count = 0;   // Inicia o XP para o n�vel atual no 0
    exp_to_level_up = 100;
    fill_percentage = 0;
    filled_width = 0;
}

bool AddToExp(int experience) {
	exp_count += experience;

    if (exp_count >= exp_to_level_up) {
        level++;
        exp_count = 0;
        exp_to_level_up += exp_increment_per_level_up;
        return true;
    }
    return false;
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
