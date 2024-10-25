/*******************************************************************************************
*
*   raylib - classic game: space invaders
*
*   Sample game developed by Ian Eito, Albert Martos and Ramon Santamaria
*
*   This game has been created using raylib v1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "math.h"
#include "resource_dir.h"

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define NUM_SHOOTS 500
#define NUM_MAX_ENEMIES 50
#define FIRST_WAVE 10
#define SECOND_WAVE 20
#define THIRD_WAVE 50

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum { FIRST = 0, SECOND, THIRD } EnemyWave;

typedef struct Player {
    Rectangle rec;
    Vector2 speed;
    Color color;
} Player;

typedef struct Enemy {
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} Enemy;

typedef struct Shoot {
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
} Shoot;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 1200;

static bool gameOver = false;
static bool pause = false;
static int score = 0;
static bool victory = false;

static Player player = { 0 };
static Enemy enemy[NUM_MAX_ENEMIES] = { 0 };
static Shoot shoot[NUM_SHOOTS] = { 0 };
static EnemyWave wave = { 0 };

static int shootRate = 0;
static float alpha = 0.0f;

static int activeEnemies = 0;
static int enemiesKill = 0;
static bool smooth = false;


// TEXTURES
Texture player_ship;
Texture background;
Texture player_assets;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

    

    // Initialization (Note windowTitle is unused on Android)
    //---------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "classic game: space invaders");

    SearchAndSetResourceDir("resources");

    player_ship = LoadTexture("ships.png");
    background = LoadTexture("purplebg.png");
    player_assets = LoadTexture("playerassets.png");
    

    InitGame();



    SetTargetFPS(120);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update and Draw
        //----------------------------------------------------------------------------------
        UpdateDrawFrame();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();         // Unload loaded data (textures, sounds, models...)

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(void)
{
    // Initialize game variables
    shootRate = 0;
    pause = false;
    gameOver = false;
    victory = false;
    smooth = false;
    wave = FIRST;
    activeEnemies = FIRST_WAVE;
    enemiesKill = 0;
    score = 0;
    alpha = 0;

    // Initialize player
    player.rec.x = 20;
    player.rec.y = 50;
    player.rec.width = 48;
    player.rec.height = 48;
    player.speed.x = 5;
    player.speed.y = 5;
    player.color = BLACK;

    // Initialize enemies
    for (int i = 0; i < NUM_MAX_ENEMIES; i++)
    {
        enemy[i].rec.width = 10;
        enemy[i].rec.height = 10;
        enemy[i].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
        enemy[i].rec.y = GetRandomValue(0, screenHeight - enemy[i].rec.height);
        enemy[i].speed.x = 5;
        enemy[i].speed.y = 5;
        enemy[i].active = true;
        enemy[i].color = GRAY;
    }

    // Initialize shoots
    for (int i = 0; i < NUM_SHOOTS; i++)
    {
        shoot[i].rec.x = player.rec.x + player.rec.width / 4;
        shoot[i].rec.y = player.rec.y;
        shoot[i].rec.width = 6;
        shoot[i].rec.height = 10;
        shoot[i].speed.x = 0;
        shoot[i].speed.y = 7;
        shoot[i].active = false;
        shoot[i].color = MAROON;
    }
}

// Update game (one frame)
void UpdateGame(void)
{
    if (!gameOver)
    {
        if (IsKeyPressed('P')) pause = !pause;

        if (!pause)
        {
            switch (wave)
            {
            case FIRST:
            {
                if (!smooth)
                {
                    alpha += 0.02f;

                    if (alpha >= 1.0f) smooth = true;
                }

                if (smooth) alpha -= 0.02f;

                if (enemiesKill == activeEnemies)
                {
                    enemiesKill = 0;

                    for (int i = 0; i < activeEnemies; i++)
                    {
                        if (!enemy[i].active) enemy[i].active = true;
                    }

                    activeEnemies = SECOND_WAVE;
                    wave = SECOND;
                    smooth = false;
                    alpha = 0.0f;
                }
            } break;
            case SECOND:
            {
                if (!smooth)
                {
                    alpha += 0.02f;

                    if (alpha >= 1.0f) smooth = true;
                }

                if (smooth) alpha -= 0.02f;

                if (enemiesKill == activeEnemies)
                {
                    enemiesKill = 0;

                    for (int i = 0; i < activeEnemies; i++)
                    {
                        if (!enemy[i].active) enemy[i].active = true;
                    }

                    activeEnemies = THIRD_WAVE;
                    wave = THIRD;
                    smooth = false;
                    alpha = 0.0f;
                }
            } break;
            case THIRD:
            {
                if (!smooth)
                {
                    alpha += 0.02f;

                    if (alpha >= 1.0f) smooth = true;
                }

                if (smooth) alpha -= 0.02f;

                if (enemiesKill == activeEnemies) victory = true;

            } break;
            default: break;
            }

            // Player movement
            if (IsKeyDown(KEY_RIGHT)) player.rec.x += player.speed.x;
            if (IsKeyDown(KEY_LEFT)) player.rec.x -= player.speed.x;
            if (IsKeyDown(KEY_UP)) player.rec.y -= player.speed.y;
            if (IsKeyDown(KEY_DOWN)) player.rec.y += player.speed.y;

            // Player collision with enemy
            for (int i = 0; i < activeEnemies; i++)
            {
                if (CheckCollisionRecs(player.rec, enemy[i].rec)) gameOver = true;

            }

            // Enemy behaviour
            for (int i = 0; i < activeEnemies; i++)
            {
                if (enemy[i].active)
                {
                    enemy[i].rec.y += enemy[i].speed.y;

                    if (enemy[i].rec.y > screenHeight)
                    {
                        enemy[i].rec.x = GetRandomValue(0, screenWidth - enemy[i].rec.width);
                        enemy[i].rec.y = GetRandomValue(-200, -400);
                    }
                }
            }

            // Wall behaviour
            if (player.rec.x <= 0) player.rec.x = 0;
            if (player.rec.x + player.rec.width >= screenWidth) player.rec.x = screenWidth - player.rec.width;
            if (player.rec.y <= 0) player.rec.y = 0;
            if (player.rec.y + player.rec.height >= screenHeight) player.rec.y = screenHeight - player.rec.height;

            // Shoot initialization
            if (IsKeyDown(KEY_SPACE))
            {
                shootRate += 5;

                for (int i = 0; i < NUM_SHOOTS; i++)
                {
                    if (!shoot[i].active && shootRate % 20 == 0)
                    {
                        shoot[i].rec.x = player.rec.x + (player.rec.width/2) - 3;
                        shoot[i].rec.y = player.rec.y-8;
                        shoot[i].active = true;
                        break;
                    }
                }
            }

            // Shoot logic
            for (int i = 0; i < NUM_SHOOTS; i++)
            {
                if (shoot[i].active)
                {
                    // Movement
                    shoot[i].rec.y -= shoot[i].speed.y;

                    // Collision with enemy
                    for (int j = 0; j < activeEnemies; j++)
                    {
                        if (enemy[j].active)
                        {
                            if (CheckCollisionRecs(shoot[i].rec, enemy[j].rec))
                            {
                                shoot[i].active = false;
                                enemy[j].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
                                enemy[j].rec.y = GetRandomValue(0, screenHeight - enemy[j].rec.height);
                                shootRate = 0;
                                enemiesKill++;
                                score += 100;
                            }

                            if (shoot[i].rec.y < -10)
                            {
                                shoot[i].active = false;
                                shootRate = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            InitGame();
            gameOver = false;
        }
    }
}

Rectangle GetPlayerRectangle() {
    if (IsKeyDown(KEY_RIGHT)) {
        Rectangle player_texture_right = { 16, 0, 8, 8 };
        return player_texture_right;
    }
    else if (IsKeyDown(KEY_LEFT)) {
        Rectangle player_texture_left = { 0, 0, 8, 8 };
        return player_texture_left;
    }
    Rectangle player_texture_center = { 8, 0, 8, 8 };
    return player_texture_center;
}

Rectangle GetThrusters(int cycle) {
    switch (abs(cycle)) {
    case 1:
        return (Rectangle) { 40, 8, 8, 8 };
    case 2:
        return (Rectangle) { 48, 8, 8, 8 };
    case 3:
        return (Rectangle) { 56, 8, 8, 8 };
    default:
        return (Rectangle) { 64, 8, 8, 8 };
    }
}

int bg_pos_y = -1200;
int fire_offset = 0;
float thruster_cycle = 0;

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();

    ClearBackground(BLACK);
    
    Vector2 player_pos = { 4, 4 };
    Color bg_color = { 255, 255, 255, 170 };
    
    if (!gameOver)
    {
        bg_pos_y = (bg_pos_y + 5) % 2400;
        DrawTexture(background, 0, bg_pos_y, bg_color);
        DrawTexture(background, 0, bg_pos_y - 2400, bg_color);

        if (IsKeyDown(KEY_RIGHT)) {
            fire_offset = 8;
            thruster_cycle -= 0.2;
        }
        else if (IsKeyDown(KEY_LEFT)) {
            fire_offset = -8;
        }
        else {
            fire_offset = 0;
        }
        
        Rectangle player_texture2 = { player.rec.x-4, player.rec.y-8, 64, 64 };
        Rectangle thruster_position = { player.rec.x - 4 + fire_offset, player.rec.y + 48, 64, 64 };

        thruster_cycle = fmod((thruster_cycle + 0.1f), 4.0f);
        
        DrawTexturePro(player_ship, GetPlayerRectangle(), player_texture2, player_pos, 0, WHITE);
        DrawTexturePro(player_assets, GetThrusters(thruster_cycle), thruster_position, player_pos, 0, WHITE);
        

        if (wave == FIRST) DrawText("FIRST WAVE", screenWidth / 2 - MeasureText("FIRST WAVE", 40) / 2, screenHeight / 2 - 40, 40, Fade(BLACK, alpha));
        else if (wave == SECOND) DrawText("SECOND WAVE", screenWidth / 2 - MeasureText("SECOND WAVE", 40) / 2, screenHeight / 2 - 40, 40, Fade(BLACK, alpha));
        else if (wave == THIRD) DrawText("THIRD WAVE", screenWidth / 2 - MeasureText("THIRD WAVE", 40) / 2, screenHeight / 2 - 40, 40, Fade(BLACK, alpha));

        for (int i = 0; i < activeEnemies; i++)
        {
            if (enemy[i].active) DrawRectangleRec(enemy[i].rec, enemy[i].color);
        }

        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (shoot[i].active) DrawRectangleRec(shoot[i].rec, shoot[i].color);
        }

        DrawText(TextFormat("%04i", score), 20, 20, 40, GRAY);

        if (victory) DrawText("YOU WIN", screenWidth / 2 - MeasureText("YOU WIN", 40) / 2, screenHeight / 2 - 40, 40, BLACK);

        if (pause) DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2, screenHeight / 2 - 40, 40, GRAY);
    }
    else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    
    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    UnloadTexture(player_ship);
    UnloadTexture(background);
    UnloadTexture(player_assets);
    
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}