/*******************************************************************************************
*
*   Space Invaders - Edição Roguelike
*
*   Jogo desenvolvido por Luís Filipe Macedo, Anderson Gabriel e Débora Souza
*
*   Esse jogo foi criado usando Raylib (www.raylib.com)
*
********************************************************************************************/

//--------------------------------------------------------------
//
//                         IMPORTS
// 
//--------------------------------------------------------------

// Raylib
#include "raylib.h"
#include "resource_dir.h"

// Outras libs
#include "math.h"

// Nossos próprios includes
#include "common.h"
#include "draw_object.h"

#include "scene_manager.h"

#include "player.h"
#include "enemy.h"
#include "weapon.h"
#include "power_ups.h"

#include "main_menu.h"
#include "select_ship.h"

#include "tutorial.h"
#include "game.h"

static Scene starting_scene = START;

void LoadGame(void);
void UnloadGame(void);

//--------------------------------------------------------------
//
//                           MAIN
// 
//--------------------------------------------------------------

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders"); // Inicializa a janela do jogo

    SetTargetFPS(240);

    LoadGame();         // Inicializa o diretório de recursos/assets e as texturas
    
    InitSceneManager(starting_scene);

    LoopScene();

    UnloadGame();           // Free

    CloseWindow();          // Fecha a janela

    return 0;
}

// Inicializa as texturas no jogo
void LoadGame() {
    SearchAndSetResourceDir("resources");

    LoadMenuBackgroundTexture();
    LoadSelectMenuTextures();
    LoadObjectTextures();
    LoadEnemyTextures();
    LoadGameTextures();
    LoadTutorialTextures();
    LoadWeaponTextures();
    LoadPowerUpTextures();
}


// Unload game variables
void UnloadGame(void)
{
    UnloadObjectTextures();
    UnloadEnemyTextures();
    UnloadSelectMenuTextures();
    UnloadMenuBackgroundTexture();
    UnloadTutorialTextures();
    UnloadWeaponTextures();
    UnloadPowerUpTextures();
}