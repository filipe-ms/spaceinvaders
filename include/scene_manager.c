// scene_manager.c

#include "scene_manager.h"
#include "select_ship.h"
#include "main_menu.h"
#include "game.h"
#include "tutorial.h"

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

    case SELECT_SHIP:
        InitSelectMenu();
        break;

    case TUTORIAL:
        InitTutorial(id);
        break;

    case GAME:
        InitGame(id);
        break;
    }
}


void UpdateCurrentScene(void) {

    switch (current_scene) {

    case START:
        UpdateMenu();
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
    }
}

void DrawCurrentScene(void) {

    switch (current_scene) {

    case START:
        DrawMenu();
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
    }
}

void LoopScene() {
    while (!WindowShouldClose() && current_scene != EXIT) {
        UpdateCurrentScene();
        DrawCurrentScene();
    }
}
