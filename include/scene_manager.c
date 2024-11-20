// scene_manager.c

#include "scene_manager.h"
#include "select_ship.h"
#include "main_menu.h"
#include "game.h"
#include "tutorial.h"
#include "ranking.h"
#include "enter_name.h"
#include "winner.h"
#include "game_over.h"

Scene current_scene;
Scene main_menu;

void InitSceneManager(Scene scene) {
    ChangeScene(scene);
}

void ChangeScene(Scene scene) {
    ChangeSceneArgs(scene, 0);
}

void ChangeSceneArgs(Scene scene, int id) {
    current_scene = scene;

    switch (current_scene) {
    case START:
        InitMenu();
        break;

    case RANKING:
        InitRanking();
        break;

    case SELECT_SHIP:
        InitSelectMenu();
        break;

    case TUTORIAL:
        InitTutorial(id);
        break;

    case GAME:
        InitGame(id);
        break;

    case ENTER_NAME:
        InitEnterName();
        break;

    case WINNER:
        InitWinner();
        break;

	case GAME_OVER:
		InitGameOver();
		break;
    }
}


void UpdateCurrentScene(void) {

    switch (current_scene) {

    case START:
        UpdateMenu();
        break;

	case RANKING:
		UpdateRanking();
		break;

    case SELECT_SHIP:
        UpdateShipSelectMenu();
        break;

    case TUTORIAL:
        UpdateTutorial();
        break;

    case GAME:
        UpdateGame();
        break;

    case ENTER_NAME:
        UpdateEnterName();
        break;

    case WINNER:
        UpdateWinner();
        break;

    case GAME_OVER:
        UpdateGameOver();
        break;
    }

}

void DrawCurrentScene(void) {

    switch (current_scene) {

    case START:
        DrawMenu();
        break;

    case RANKING:
        DrawRanking(100, 100);
        break;

    case SELECT_SHIP:
        DrawSelectMenu();
        break;

    case TUTORIAL:
        DrawTutorial();
        break;

    case GAME:
        DrawGame();
        break;

	case ENTER_NAME:
        DrawEnterName();
        break;

    case WINNER:
        DrawWinner();
        break;

    case GAME_OVER:
        DrawGameOver();
        break;
    }
}

void LoopScene() {
    while (!WindowShouldClose() && current_scene != EXIT) {
        UpdateCurrentScene();
        DrawCurrentScene();
    }
}
