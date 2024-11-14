// power_ups.c

#include "power_ups.h"
#include "common.h"
#include <string.h>
#include <stdio.h>


PowerUp values[3];
int current_option = 0;
float power_up_alpha = 0.0f;

//--------------------------------------------------------------
//
//                      Shoot Cooldown
// 
//--------------------------------------------------------------

PowerUp shoot_cooldown;

void InitShootCooldownPower() {
    shoot_cooldown.effect = SHOOT_COOLDOWN;
    int value_randomizer = GetRandomValue(3, 6);
    shoot_cooldown.value = value_randomizer / 100.0f; 
    sprintf(shoot_cooldown.description_line_1, "Vel. de");
    sprintf(shoot_cooldown.description_line_2, "ataque");
    sprintf(shoot_cooldown.description_line_3, "+ %d%%", (int)(shoot_cooldown.value*100));
    shoot_cooldown.color = WHITE; 
}

//--------------------------------------------------------------
//
//                      Shoot Damage
// 
//--------------------------------------------------------------

PowerUp shoot_damage;

void InitShootDamagePower() {
    shoot_damage.effect = SHOOT_DAMAGE;
    int value_randomizer = GetRandomValue(10, 25);
    shoot_damage.value = value_randomizer / 100.0f;
    sprintf(shoot_damage.description_line_1, "Dano de");
    sprintf(shoot_damage.description_line_2, "ataque");
	sprintf(shoot_damage.description_line_3, "+ %d%%", (int)(shoot_damage.value*100));
    shoot_damage.color = WHITE;
}

//--------------------------------------------------------------
//
//                      Shoot Size
// 
//--------------------------------------------------------------

PowerUp shoot_size;

void InitShootSizePower() {
    shoot_size.effect = SHOOT_SIZE;
	int value_randomizer = GetRandomValue(10, 20);
    shoot_size.value = value_randomizer / 100.0f;
    sprintf(shoot_size.description_line_1, "Tamanho de");
    sprintf(shoot_size.description_line_2, "ataques");
    sprintf(shoot_size.description_line_3, "+ %d%%", (int)(shoot_size.value*100));
    shoot_size.color = WHITE;
}

//--------------------------------------------------------------
//
//                          Update
// 
//--------------------------------------------------------------

void GetLevelUpPowers() {
    values[0] = shoot_cooldown;
    values[1] = shoot_damage;
    values[2] = shoot_size;
    current_option = 0;
}

void PowerRandomizer(void) {

	InitShootCooldownPower();
	InitShootDamagePower();
	InitShootSizePower();

	GetLevelUpPowers();
}

PowerUp GetPowerUp(int type) {
	switch (type) {
	    case SHOOT_COOLDOWN: return shoot_cooldown;
	    case SHOOT_DAMAGE: return shoot_damage;
	    case SHOOT_SIZE: return shoot_size;
		default: return shoot_cooldown;
	}
}

void PickPowerUp() {
	PowerUp power = values[current_option];
	switch (power.effect) {
	    case SHOOT_COOLDOWN:
            IncrementCooldownModifier(power.value); 
            break;
        case SHOOT_DAMAGE: 
            IncrementDamageModifier(power.value);
            break;
	    case SHOOT_SIZE: 
            IncrementSizeModifier(power.value);
            break;
	}
	for (int i = 0; i < 3; i++) {
		values[i].effect = NONE;
	}

}

PowerUp UpdateLevelUpSelectMenu(bool *flag) {
	if (*flag) {

		if (power_up_alpha < 1.0f) power_up_alpha += 0.5f * GetFrameTime();

		if (IsKeyPressed(KEY_RIGHT)) {
			current_option++;
			if (current_option > 2) current_option = 0;
		}

		else if (IsKeyPressed(KEY_LEFT)) {
			current_option--;
			if (current_option < 0) current_option = 2;
		}

		else if (IsKeyPressed(KEY_ENTER)) {
			*flag = false;
            PickPowerUp();
		}
    }
    else {
		power_up_alpha = 0.0f;
    }
    return (PowerUp) { NONE, 0.0f, { 0 }, { 0 }, { 0 }, { 0 }, WHITE };

}

//--------------------------------------------------------------
//
//                          Draw
// 
//--------------------------------------------------------------


void DrawMultilineText(const char* line1, const char* line2, const char* line3, float x, float y, int fontSize, Color color, float alpha) {
    DrawText(line1, x, y, fontSize, Fade(color, alpha)); 
    DrawText(line2, x, y + fontSize + 5, fontSize, Fade(color, alpha)); 
    DrawText(line3, x, y + 2 * (fontSize + 5), fontSize, Fade(color, alpha));
}

void DrawLevelUpSelectMenu(bool flag) {
    if (flag) {
        DrawText("Selecione um poder", (int)(SCREEN_WIDTH / 2 - MeasureText("Selecione um poder", 40) / 2), (int)(SCREEN_HEIGHT / 2 - 350), 40, Fade(WHITE, power_up_alpha));

        int card_width = values[0].texture.width;

        float texture_1_x_pos = (float)(SCREEN_WIDTH * 0.25 - card_width * 0.25 / 2);
        float texture_2_x_pos = (float)(SCREEN_WIDTH * 0.5 - card_width * 0.25 / 2);
        float texture_3_x_pos = (float)(SCREEN_WIDTH * 0.75 - card_width * 0.25 / 2);

        float y_pos = (float)(SCREEN_HEIGHT / 2) - 250;
        float text_y_offset = (float)(SCREEN_HEIGHT / 2) - 50;

        Color card_1 = (current_option == 0) ? Fade(RED, power_up_alpha) : Fade(GRAY, power_up_alpha);
        Color card_2 = (current_option == 1) ? Fade(RED, power_up_alpha) : Fade(GRAY, power_up_alpha);
        Color card_3 = (current_option == 2) ? Fade(RED, power_up_alpha) : Fade(GRAY, power_up_alpha);

        Rectangle border_1 = { texture_1_x_pos - 4, y_pos - 4, card_width * 0.25 + 8, (float)(values[0].texture.height * 0.25 + 8) };
        Rectangle border_2 = { texture_2_x_pos - 4, y_pos - 4, card_width * 0.25 + 8, (float)(values[0].texture.height * 0.25 + 8) };
        Rectangle border_3 = { texture_3_x_pos - 4, y_pos - 4, card_width * 0.25 + 8, (float)(values[0].texture.height * 0.25 + 8) };
        
        DrawRectangleLinesEx(border_1, 16, card_1);
        DrawRectangleLinesEx(border_2, 16, card_2);
        DrawRectangleLinesEx(border_3, 16, card_3);

        Rectangle rec_1 = { texture_1_x_pos - 4, y_pos + 200, card_width * 0.25 + 8, (float)(values[0].texture.height * 0.25 /2 - 8) };
        Rectangle rec_2 = { texture_2_x_pos - 4, y_pos + 200, card_width * 0.25 + 8, (float)(values[0].texture.height * 0.25 /2 - 8) };
        Rectangle rec_3 = { texture_3_x_pos - 4, y_pos + 200, card_width * 0.25 + 8, (float)(values[0].texture.height * 0.25 /2 - 8) };

        DrawRectangleRec(rec_1, Fade(BLACK, power_up_alpha));
        DrawRectangleRec(rec_2, Fade(BLACK, power_up_alpha));
        DrawRectangleRec(rec_3, Fade(BLACK, power_up_alpha));

        DrawTextureEx(values[0].texture, (Vector2) { texture_1_x_pos, y_pos }, 0, 0.25f, Fade(WHITE, power_up_alpha));
        DrawTextureEx(values[1].texture, (Vector2) { texture_2_x_pos, y_pos }, 0, 0.25f, Fade(WHITE, power_up_alpha));
        DrawTextureEx(values[2].texture, (Vector2) { texture_3_x_pos, y_pos }, 0, 0.25f, Fade(WHITE, power_up_alpha));

        DrawMultilineText(values[0].description_line_1, values[0].description_line_2, values[0].description_line_3, texture_1_x_pos + 4, text_y_offset + 8, 20, WHITE, power_up_alpha);
        DrawMultilineText(values[1].description_line_1, values[1].description_line_2, values[1].description_line_3, texture_2_x_pos + 4, text_y_offset + 8, 20, WHITE, power_up_alpha);
        DrawMultilineText(values[2].description_line_1, values[2].description_line_2, values[2].description_line_3, texture_3_x_pos + 4, text_y_offset + 8, 20, WHITE, power_up_alpha);
    }
}
//--------------------------------------------------------------
void LoadPowerUpTextures(void) {
	shoot_cooldown.texture = LoadTexture("cooldown.png");
	shoot_damage.texture = LoadTexture("damage.png");
	shoot_size.texture = LoadTexture("size.png");
}

void UnloadPowerUpTextures(void) {
	UnloadTexture(shoot_cooldown.texture);
	UnloadTexture(shoot_damage.texture);
	UnloadTexture(shoot_size.texture);
}




/*








void InitShootRatePowerUp(struct PowerUpShootRate* power) {
    power->rec.width = 20;  // Define a largura do item
    power->rec.height = 20; // Define a altura do item
    power->rec.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(power->rec.width));  // Posição aleatória x
    power->rec.y = (float)GetRandomValue(0, SCREEN_HEIGHT - (int)(power->rec.height)); // Posição aleatória y
    power->active = true;   // Item começa ativo
    power->color = RED;     // Define a cor do item como vermelha
}

void SpawnShootRatePowerUp(struct PowerUpShootRate* power) {
    if (!power->active) {
        // Ativa o item e define uma nova posição aleatória quando a segunda onda começa
        power->rec.x = (float)GetRandomValue(0, SCREEN_WIDTH - (int)(power->rec.width));
        power->rec.y = (float)GetRandomValue(0, SCREEN_HEIGHT - (int)(power->rec.height));
        power->active = true;
    }
}

void DrawPowerUps(struct PowerUpShootRate power) {
    if (power.active) {
        DrawRectangleRec(power.rec, power.color);
    }
}

void UpdatePowerUp(struct PowerUpShootRate* power, struct Weapon* weapon, struct Player player) {
    if (power->active && CheckCollisionRecs(player.position, power->rec)) {
        // Diminui o intervalo de frame do shootRate em 20%
        weapon[0].charge_time_modifier += 0.2f;

        // Desativa o item após coleta
        power->active = false;
    }
}
*/