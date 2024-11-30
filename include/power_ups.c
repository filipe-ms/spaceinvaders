// power_ups.c

#include "power_ups.h"
#include "common.h"
#include "weapon.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

PowerUp values[3];
int current_option = 0;
float power_up_alpha = 0.0f;

//--------------------------------------------------------------
//
//                      List for Random
// 
//--------------------------------------------------------------

typedef struct Node {
	int val;
	struct Node* next;
} Node;

typedef struct List {
	int count;
	Node* head;
} List;

static void AddToList(List* list, int val) {
	Node *new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) return;
	new_node->val = val;
	new_node->next = list->head;
	list->head = new_node;
	list->count++;
}

static int CheckValueInIndex(List* list, int index) {
	Node* current = list->head;
	int i = 0;
	while (current != NULL) {
		if (i == index) return current->val;
		i++;
		current = current->next;
	}
	return -1;
}

static void FreeElementInIndex(List* list, int index) {
	if (list->head == NULL) return;

	Node* current = list->head;

	if (index == 0) {
		list->head = current->next;
		free(current);
		list->count--;
		return;
	}

	for (int i = 0; current != NULL && i < index - 1; i++) {
		current = current->next;
	}

	if (current == NULL || current->next == NULL) return;

	Node* temp = current->next->next;
	free(current->next);
	list->count--;
	current->next = temp;
}

static void FreeList(List* list) {
	Node* current = list->head;
	Node* next = NULL;
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
		list->count = 0;
	}
}


//--------------------------------------------------------------
//
//                      Shoot Cooldown
// 
//--------------------------------------------------------------

PowerUp shoot_cooldown;

void InitShootCooldownPower() {
    shoot_cooldown.effect = SHOOT_COOLDOWN;
    int value_randomizer = GetRandomValue(4, 8);
    shoot_cooldown.value = value_randomizer / 100.0f; 
    sprintf(shoot_cooldown.description_line_1, "Regarga de");
    sprintf(shoot_cooldown.description_line_2, "ataques");
    sprintf(shoot_cooldown.description_line_3, "+%.2f", shoot_cooldown.value);
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
	sprintf(shoot_damage.description_line_3, "+%.2f", (shoot_damage.value));
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
    sprintf(shoot_size.description_line_3, "+%d%%", (int)(shoot_size.value*100));
    shoot_size.color = WHITE;
}

//--------------------------------------------------------------
//
//                        New Weapon
// 
//--------------------------------------------------------------

PowerUp new_weapon_pulse;
PowerUp new_weapon_photon;
PowerUp new_weapon_shotgun;

void InitNewWeaponPower() {
	new_weapon_pulse.effect = WEAPON_PULSE;
	new_weapon_photon.effect = WEAPON_PHOTON;
	new_weapon_shotgun.effect = WEAPON_SHOTGUN;

    new_weapon_pulse.value = PULSE;
	new_weapon_photon.value = PHOTON;
	new_weapon_shotgun.value = SHOTGUN;

	sprintf(new_weapon_pulse.description_line_1, "Phaser");
	sprintf(new_weapon_pulse.description_line_2, "Velocidade:");
	sprintf(new_weapon_pulse.description_line_3, "Alta");
    new_weapon_pulse.color = WHITE;

	sprintf(new_weapon_photon.description_line_1, "Photon");
	sprintf(new_weapon_photon.description_line_2, "Velocidade:");
	sprintf(new_weapon_photon.description_line_3, "Regular");
	new_weapon_photon.color = WHITE;

	sprintf(new_weapon_shotgun.description_line_1, "Shotgun");
	sprintf(new_weapon_shotgun.description_line_2, "Velocidade:");
	sprintf(new_weapon_shotgun.description_line_3, "Baixa");
	new_weapon_shotgun.color = WHITE;
}



//--------------------------------------------------------------
//
//                          Update
// 
//--------------------------------------------------------------

PowerUp GetPowerUpReference(int effect) {
	switch (effect) {
		case SHOOT_COOLDOWN:
			return shoot_cooldown;
		case SHOOT_DAMAGE:
			return shoot_damage;
		case SHOOT_SIZE:
			return shoot_size;
		case WEAPON_PULSE:
			return new_weapon_pulse;
		case WEAPON_PHOTON:
			return new_weapon_photon;
		case WEAPON_SHOTGUN:
			return new_weapon_shotgun;
		default:
			return (PowerUp) { NONE, 0.0f, { 0 }, { 0 }, { 0 }, { 0 }, WHITE };
		}
}


void GetRandomPowers() {
	List power_ref_list;
	power_ref_list.count = 0;
	power_ref_list.head = NULL;
	
    AddToList(&power_ref_list, SHOOT_COOLDOWN);
    AddToList(&power_ref_list, SHOOT_DAMAGE);
    AddToList(&power_ref_list, SHOOT_SIZE);

	if(!IsPulseActive()) AddToList(&power_ref_list, WEAPON_PULSE);
    if(!IsPhotonActive()) AddToList(&power_ref_list, WEAPON_PHOTON);
	if(!IsShotgunActive()) AddToList(&power_ref_list, WEAPON_SHOTGUN);

	for (int i = 0; i < 3; i++) {
        int index = GetRandomValue(0, (power_ref_list.count)-1);
		int index_val = CheckValueInIndex(&power_ref_list, index);
		values[i] = GetPowerUpReference(index_val);
		FreeElementInIndex(&power_ref_list, index);
    }

	FreeList(&power_ref_list);
}

void PowerRandomizer(void) {

	InitShootCooldownPower();
	InitShootDamagePower();
	InitShootSizePower();
	InitNewWeaponPower();

    GetRandomPowers();
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
        case WEAPON_PULSE:
            ActivatePulse();
            break;
        case WEAPON_PHOTON:
            ActivatePhoton();
            break;
        case WEAPON_SHOTGUN:
            ActivateShotgun();
            break;
	}

	for (int i = 0; i < 3; i++) {
		values[i].effect = NONE;
	}

}

PowerUp UpdateLevelUpSelectMenu(bool* flag) {
	if (*flag) {
		if (power_up_alpha < 1.0f) power_up_alpha += 0.5f * GetFrameTime();

		// Navegação no teclado ou no gamepad
		if (IsKeyPressed(KEY_RIGHT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_RIGHT)) {
			current_option++;
			if (current_option > 2) current_option = 0;
		}
		else if (IsKeyPressed(KEY_LEFT) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_LEFT_FACE_LEFT)) {
			current_option--;
			if (current_option < 0) current_option = 2;
		}
		// Seleção no teclado ou no gamepad
		else if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
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
    DrawText(line1, (int)((x + 32) - MeasureText(line1, fontSize) / 2.0f), (int)y, fontSize, Fade(color, alpha));
    DrawText(line2, (int)((x + 32) - MeasureText(line2, fontSize) / 2.0f), (int)y+30, fontSize, Fade(color, alpha));
    DrawText(line3, (int)((x + 32) - MeasureText(line3, fontSize) / 2.0f), (int)y+60, fontSize, Fade(color, alpha));
}

void DrawLevelUpSelectMenu(bool flag) {
    if (flag) {
        DrawText("Selecione um poder", (int)(SCREEN_WIDTH / 2 - MeasureText("Selecione um poder", 40) / 2), (int)(SCREEN_HEIGHT / 2 - 350), 40, Fade(WHITE, power_up_alpha));

        int card_width = values[0].texture.width;
		int card_height = values[0].texture.height;

        float texture_1_x_pos = (float)(SCREEN_WIDTH * 0.25 - (card_width * 2.5 / 2)-32);
        float texture_2_x_pos = (float)(SCREEN_WIDTH * 0.5 - (card_width * 2.5 / 2));
        float texture_3_x_pos = (float)(SCREEN_WIDTH * 0.75 - (card_width * 2.5 / 2)+32);

        float y_pos = (float)(SCREEN_HEIGHT / 2) - 250;
        float text_y_offset = (float)(SCREEN_HEIGHT / 2) - 50;

        Color card_1 = (current_option == 0) ? Fade(RED, power_up_alpha) : Fade(GRAY, power_up_alpha);
        Color card_2 = (current_option == 1) ? Fade(RED, power_up_alpha) : Fade(GRAY, power_up_alpha);
        Color card_3 = (current_option == 2) ? Fade(RED, power_up_alpha) : Fade(GRAY, power_up_alpha);

        Rectangle border_1 = { texture_1_x_pos - 4, y_pos - 4, card_width * 2.5f + 8, (float)(card_height * 2.5 + 8) };
        Rectangle border_2 = { texture_2_x_pos - 4, y_pos - 4, card_width * 2.5f + 8, (float)(card_height * 2.5 + 8) };
        Rectangle border_3 = { texture_3_x_pos - 4, y_pos - 4, card_width * 2.5f + 8, (float)(card_height * 2.5 + 8) };
        
        DrawRectangleLinesEx(border_1, 16, card_1);
        DrawRectangleLinesEx(border_2, 16, card_2);
        DrawRectangleLinesEx(border_3, 16, card_3);

        Rectangle rec_1 = { texture_1_x_pos - 24, y_pos + 145, 180, (float)(card_height + 40) };
        Rectangle rec_2 = { texture_2_x_pos - 24, y_pos + 145, 180, (float)(card_height + 40) };
        Rectangle rec_3 = { texture_3_x_pos - 24, y_pos + 145, 180, (float)(card_height + 40) };

        DrawRectangleRec(rec_1, Fade(BLACK, power_up_alpha));
        DrawRectangleRec(rec_2, Fade(BLACK, power_up_alpha));
        DrawRectangleRec(rec_3, Fade(BLACK, power_up_alpha));

        DrawTextureEx(values[0].texture, (Vector2) { texture_1_x_pos, y_pos }, 0, 2.5, Fade(WHITE, power_up_alpha));
        DrawTextureEx(values[1].texture, (Vector2) { texture_2_x_pos, y_pos }, 0, 2.5, Fade(WHITE, power_up_alpha));
        DrawTextureEx(values[2].texture, (Vector2) { texture_3_x_pos, y_pos }, 0, 2.5, Fade(WHITE, power_up_alpha));

        DrawMultilineText(values[0].description_line_1, values[0].description_line_2, values[0].description_line_3, texture_1_x_pos + 32, text_y_offset - 56, 30, WHITE, power_up_alpha);
        DrawMultilineText(values[1].description_line_1, values[1].description_line_2, values[1].description_line_3, texture_2_x_pos + 32, text_y_offset - 56, 30, WHITE, power_up_alpha);
        DrawMultilineText(values[2].description_line_1, values[2].description_line_2, values[2].description_line_3, texture_3_x_pos + 32, text_y_offset - 56, 30, WHITE, power_up_alpha);
    }
}

//--------------------------------------------------------------
void LoadPowerUpTextures(void) {

	shoot_cooldown.texture = LoadTexture("powerups/speed.png");
	shoot_damage.texture = LoadTexture("powerups/damage.png");
	shoot_size.texture = LoadTexture("powerups/size.png");

    new_weapon_pulse.texture = LoadTexture("powerups/pulse.png");
    new_weapon_photon.texture = LoadTexture("powerups/photon.png");
    new_weapon_shotgun.texture = LoadTexture("powerups/shotgun.png");
}

void UnloadPowerUpTextures(void) {
	UnloadTexture(shoot_cooldown.texture);
	UnloadTexture(shoot_damage.texture);
	UnloadTexture(shoot_size.texture);

	UnloadTexture(new_weapon_pulse.texture);
	UnloadTexture(new_weapon_photon.texture);
	UnloadTexture(new_weapon_shotgun.texture);
}