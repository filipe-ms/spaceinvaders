#include "boss.h"
#include "common.h"
#include "weapon.h"
#include "stdio.h"

#define BOSS_HAVOC 0

// Boss declarations
Boss havoc;

// Texture sheets
Texture boss_texture;
Texture shoot_red_ball;
Texture boss_weapon;
Texture boss_assist;

// Texture position in sheet
Rectangle red_ball = {0, 0, 8, 8};
Rectangle texture_laser_origin = { 0, 0, 8, 8 };
Rectangle texture_lightning_middle = {8, 72, 8, 8};


// Phases
bool presentation = false;
bool phase_one = false;
bool phase_two = false;
bool phase_three = false;
bool invulnerable = false;
bool defeated = false;

// Havoc presentation
void HavocPresentation(){
	if (havoc.position.y < 100) {
		havoc.position.y += 60 * GetFrameTime();
	}


	if (havoc.position.y >= 100) {
		presentation = false;
		phase_one = true;
		invulnerable = false;
	}
}



// Havoc phase one variables (shoot)
float havoc_p1_shoot_cooldown = 3.0f;
float havoc_p1_shoot_cooldown_charge = 0.0f;
Shoot havoc_shoot[50];

void HavocShootInit() {
	havoc_p1_shoot_cooldown_charge += GetFrameTime();
	if (havoc_p1_shoot_cooldown_charge >= havoc_p1_shoot_cooldown) {
		for (int i = 0; i < 50; i++) {
			if (!havoc_shoot[i].active) {
				havoc_shoot[i].active = true;
				havoc_shoot[i].position = (Rectangle){ havoc.position.x + havoc.position.width / 2, havoc.position.y + havoc.position.height / 2, 32, 32 };
				havoc_shoot[i].speed = (Vector2){ 0, 100 };
				havoc_p1_shoot_cooldown_charge -= havoc_p1_shoot_cooldown;
				if (havoc_p1_shoot_cooldown > 1.6f) havoc_p1_shoot_cooldown -= 0.1f;
				break;
			}
		}
	}
}

void HavocShootUpdate() {
	for (int i = 0; i < 50; i++) {
		if (havoc_shoot[i].active) {
			havoc_shoot[i].position.x += havoc_shoot[i].speed.x * GetFrameTime();
			havoc_shoot[i].position.y += havoc_shoot[i].speed.y * GetFrameTime();
			if (havoc_shoot[i].position.y > SCREEN_HEIGHT+150) havoc_shoot[i].active = false;
		}
	}
}

// Havoc phase one variables (move)
float havoc_direction_time_limit = 0.0f;
float havoc_direction_time = 0.0f;

void HavocP1Move() {
	havoc_direction_time += GetFrameTime();
	if (havoc_direction_time >= havoc_direction_time_limit) {
		havoc.speed.x *= -1;
		havoc_direction_time = 0;
		havoc_direction_time_limit = (float)GetRandomValue(1, 3);
	}

	havoc.position.x += havoc.speed.x * GetFrameTime();
	if (havoc.position.x > SCREEN_WIDTH - havoc.position.width || havoc.position.x <= 0) {
		havoc.speed.x *= -1;
	}
}

Rectangle havoc_p2_laser_origin_1_pos;
Rectangle havoc_p2_laser_origin_1_hitbox;
bool havoc_p2_beam_active = false;
int havoc_p2_beam_shooting = -1;
float havoc_p2_beam_cooldown = 5.0f;
float havoc_p2_beam_charge = 0.0f;
Vector2 havoc_p2_beam_origin_speed;
float havoc_p2_beam_alpha = 0.5f;

float havoc_lightning_alpha = 0.0f;
bool is_lightning_active = false;

void HavocP2BeamAttackInit() {
	havoc_p2_laser_origin_1_pos.x = havoc.position.x + havoc.position.width/2;
	havoc_p2_laser_origin_1_pos.y = havoc.position.y;
	havoc_p2_laser_origin_1_pos.width = 64;
	havoc_p2_laser_origin_1_pos.height = 64;
	havoc_p2_beam_origin_speed = (Vector2){ 60, 0 };
	havoc_p2_beam_active = true;
}

void HavocP2BeamAttackUpdate() {
	// Initial setup when not shooting
	if (havoc_p2_beam_shooting == -1) {
		if (havoc_p2_laser_origin_1_pos.y > havoc.position.y - 60) {
			havoc_p2_laser_origin_1_pos.y -= GetFrameTime() * 60;
		}
		else {
			havoc_p2_beam_shooting = 0;
		}
	}
	// Charging phase
	else if (havoc_p2_beam_shooting == 0) {
		havoc_p2_beam_charge += GetFrameTime();
		havoc_p2_laser_origin_1_pos.x += havoc_p2_beam_origin_speed.x * GetFrameTime();

		if (havoc_p2_laser_origin_1_pos.x >= SCREEN_WIDTH - havoc_p2_laser_origin_1_pos.width) {
			havoc_p2_beam_origin_speed.x = -60;
		}
		else if (havoc_p2_laser_origin_1_pos.x <= 0) {
			havoc_p2_beam_origin_speed.x = 60;
		}

		if (havoc_p2_beam_charge >= havoc_p2_beam_cooldown) {
			havoc_p2_beam_shooting = 1;
			havoc_p2_laser_origin_1_hitbox = havoc_p2_laser_origin_1_pos;
			havoc_p2_beam_charge = 0;
			havoc_p2_beam_alpha = 0.5f;
		}
	}
	// Shooting phase
	else if (havoc_p2_beam_shooting == 1) {
		havoc_p2_laser_origin_1_hitbox.height += 700 * GetFrameTime();
		if (havoc_p2_laser_origin_1_hitbox.height > SCREEN_HEIGHT) {
			havoc_p2_beam_shooting = 2;
		}
	}
	// Fading out phase
	else if (havoc_p2_beam_shooting == 2) {
		havoc_p2_beam_alpha -= GetFrameTime();
		if (havoc_p2_beam_alpha <= 0) {
			havoc_p2_beam_shooting = 3;
			havoc_p2_beam_alpha = 0.0f;
		}
	}
	// Lightning activation phase
	else if (havoc_p2_beam_shooting == 3) {
		havoc_lightning_alpha += GetFrameTime() * 8;
		if (havoc_lightning_alpha >= 1) {
			havoc_lightning_alpha = 1;
			havoc_p2_beam_shooting = 4;
			is_lightning_active = true;
		}
	}
	// Lightning deactivation phase
	else if (havoc_p2_beam_shooting == 4) {
		havoc_lightning_alpha -= GetFrameTime() * 8;
		if (havoc_lightning_alpha <= 0) {
			havoc_lightning_alpha = 0;
			havoc_p2_beam_shooting = 0;
			is_lightning_active = false;
		}
	}
}


void HavocShootVanish() {
	for (int i = 0; i < 50; i++) {
		if (havoc_shoot[i].active) {
			havoc_shoot[i].active = false;
		}
	}
	is_lightning_active = false;
}

void HavocP2BeamAttackDraw() {
	DrawTexturePro(boss_assist, texture_laser_origin, havoc_p2_laser_origin_1_pos, (Vector2) { 0, 0 }, 0, Fade(WHITE, havoc.alpha));
	DrawRectangleRec((Rectangle) { havoc_p2_laser_origin_1_hitbox.x + 28, havoc_p2_laser_origin_1_hitbox.y + 20, 8, havoc_p2_laser_origin_1_hitbox.height }, Fade((Color){ 240, 50, 50, 255 }, havoc_p2_beam_alpha * havoc.alpha));
	DrawRectangleRec((Rectangle) { havoc_p2_laser_origin_1_hitbox.x + 36, havoc_p2_laser_origin_1_hitbox.y + 20, 2, havoc_p2_laser_origin_1_hitbox.height }, Fade((Color) { 255, 102, 102, 255 }, havoc_p2_beam_alpha * havoc.alpha));
	DrawRectangleRec((Rectangle) { havoc_p2_laser_origin_1_hitbox.x + 26, havoc_p2_laser_origin_1_hitbox.y + 20, 2, havoc_p2_laser_origin_1_hitbox.height }, Fade((Color) { 255, 102, 102, 255 }, havoc_p2_beam_alpha * havoc.alpha));
	
	if (is_lightning_active) { 
		for (int i = 0; i < SCREEN_HEIGHT; i += 64) { 
			DrawTexturePro(boss_weapon, texture_lightning_middle, (Rectangle) { havoc_p2_laser_origin_1_hitbox.x + 48, havoc_p2_laser_origin_1_hitbox.y + 24 + i, 64, 32 }, (Vector2) { 0, 0 }, 90, Fade(WHITE, havoc_lightning_alpha)); 
		} 
	}
}

void HavocPhaseOne() {

	HavocShootInit();
	HavocP1Move();
	HavocShootUpdate();

	if (havoc.cur_hp <= havoc.max_hp * 0.5) {
		phase_one = false;
		HavocP2BeamAttackInit();
		phase_two = true;
	}
}

void HavocPhaseTwo() {

	HavocShootInit();
	HavocP1Move();
	HavocShootUpdate();
	HavocP2BeamAttackUpdate();

	if (havoc.cur_hp <= 0) {
		HavocShootVanish();
		phase_two = false;
		defeated = true;
	}
}

void HavocDefeated() {
	havoc.alpha -= GetFrameTime();
	if (havoc.alpha <= 5) {
		havoc.active = false;
	}
}

void InitHavoc() {
	havoc.id = BOSS_HAVOC;
	havoc.active = true;
	havoc.max_hp = 30.0f;
	havoc.cur_hp = 30.0f;
	havoc.alpha = 1.0f;
	havoc.position.width = 128;
	havoc.position.height = 128;
	havoc.speed.x = 120;
	havoc.speed.y = 0;
	havoc.color = WHITE;

	havoc.texture_pos = (Rectangle){ 64, 64, 16, 16 };

	presentation = true;
	invulnerable = true;

	phase_one = false;
	phase_two = false;
	defeated = false;

	// Havoc phase one variables
	havoc_p1_shoot_cooldown = 3.0f;
	havoc_p1_shoot_cooldown_charge = 0.0f;
	havoc_direction_time_limit = 0.0f;
	havoc_direction_time = 0.0f;

	
	// Havoc phase two variables

	havoc_p2_beam_active = false;
	havoc_p2_beam_shooting = -1;
	havoc_p2_beam_cooldown = 5.0f;
	havoc_p2_beam_charge = 0.0f;
	havoc_p2_beam_alpha = 0.5f;

	havoc_lightning_alpha = 0.0f;
	is_lightning_active = false;

	for (int i = 0; i < 50; i++) {
		havoc_shoot[i].active = false;
		havoc_shoot[i].damage = 1.0f;
	}

	havoc.position.x = SCREEN_WIDTH / 2 - havoc.position.width / 2;
	havoc.position.y = -200;

}

void HavocBehavior() {
	if (presentation) {
		HavocPresentation();
	}
	else if (phase_one) {
		HavocPhaseOne();
	}
	else if (phase_two) {
		HavocPhaseTwo();
	}
	else if (defeated) {
		HavocDefeated();
	}
}

void HavocDraw() {
	DrawTexturePro(boss_texture, havoc.texture_pos, havoc.position, havoc.offset, 0, Fade(WHITE, havoc.alpha));
	for (int i = 0; i < 50; i++) {
		if (havoc_shoot[i].active) {
			DrawTexturePro(shoot_red_ball, red_ball, havoc_shoot[i].position, (Vector2) { 0, 0 }, 0, WHITE);
		}
	}
	HavocP2BeamAttackDraw();
}

void InitBoss() {
	InitHavoc();
}

void UpdateBoss() {
	HavocBehavior();
}

void DrawBoss() {
	HavocDraw();
}

void LoadBossTextures() {
	shoot_red_ball = LoadTexture("shoot_red_ball.png");
	boss_texture = LoadTexture("ships.png");
	boss_assist = LoadTexture("havoc_aux.png");
	boss_weapon = LoadTexture("weapons.png");
}

void UnloadBossTextures() {
	UnloadTexture(shoot_red_ball);
	UnloadTexture(boss_texture);
	UnloadTexture(boss_assist);
	UnloadTexture(boss_weapon);
}


bool CheckBossCollisionWithPlayer(Player player) {
	if (!defeated) {
		if (CheckCollisionRecs(player.position, havoc.position)) {
			return true;
		}
		for (int i = 0; i < 50; i++) {
			if (havoc_shoot[i].active) {
				if (CheckCollisionRecs(player.position, havoc_shoot[i].position)) {
					return true;
				}
			}
		}
		if (is_lightning_active) {
			if (CheckCollisionRecs(player.position, (Rectangle) { havoc_p2_laser_origin_1_hitbox.x + 16, havoc_p2_laser_origin_1_hitbox.y + 24, 32, SCREEN_HEIGHT })) {
				return true;
			}
		}
	}
	return false;
}

bool IsBossActive(void) {
	return havoc.active;
}


bool IsBossDead(void) {
	return !havoc.active;
}

void CheckBossHit(Shoot* shoot) {
	if (IsBossActive() && !invulnerable) {
		if (CheckCollisionRecs(havoc.position, shoot->position)) {
			havoc.cur_hp -= shoot->damage;
			shoot->active = false;
			printf("%f\n", havoc.cur_hp);
		}
	}
}


