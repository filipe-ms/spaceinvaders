#include "credits.h"
#include "raylib.h"
#include "scene_manager.h"

static float fadeAlpha = 0.0f;

void InitCredits(void) {
    fadeAlpha = 0.0f;
}

void UpdateCredits(void) {
    if (IsKeyPressed(KEY_ENTER) || IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
        ChangeScene(START);
    }

    if (fadeAlpha < 1.0f) {
        fadeAlpha += 0.01f;
        if (fadeAlpha > 1.0f) fadeAlpha = 1.0f;
    }
}

void DrawCredits(void) {
    Color LIGHTBLUE = { 173, 216, 230, 255 };
    int screenWidth = 640;
    int screenHeight = 960;

    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Obrigado por jogar!", (screenWidth - MeasureText("Obrigado por jogar!", 36)) / 2, 100, 36, Fade(WHITE, fadeAlpha));

    DrawText("Equipe:", (screenWidth - MeasureText("Equipe:", 28)) / 2, 200, 28, Fade(WHITE, fadeAlpha));
    DrawText("- Anderson Gabriel", (screenWidth - MeasureText("- Anderson Gabriel", 22)) / 2, 250, 22, Fade(GRAY, fadeAlpha));
    DrawText("- Debora Souza", (screenWidth - MeasureText("- Debora Souza", 22)) / 2, 290, 22, Fade(GRAY, fadeAlpha));
    DrawText("- Luis Filipe Macedo", (screenWidth - MeasureText("- Luis Filipe Macedo", 22)) / 2, 330, 22, Fade(GRAY, fadeAlpha));

    DrawText("Agradecimento especial aos professores:", (screenWidth - MeasureText("Agradecimento especial aos professores:", 28)) / 2, 400, 28, Fade(WHITE, fadeAlpha));
    DrawText("- Pamela Bezerra", (screenWidth - MeasureText("- Pamela Bezerra", 22)) / 2, 450, 22, Fade(GRAY, fadeAlpha));
    DrawText("- Tiago Barros", (screenWidth - MeasureText("- Tiago Barros", 22)) / 2, 490, 22, Fade(GRAY, fadeAlpha));

    DrawText("e tambem agradecemos a:", (screenWidth - MeasureText("e tambem agradecemos a:", 28)) / 2, 560, 28, Fade(WHITE, fadeAlpha));
    DrawText("- Henrique Macedo", (screenWidth - MeasureText("- Henrique Macedo", 22)) / 2, 610, 22, Fade(GRAY, fadeAlpha));
    DrawText("- Gustavo Vituri", (screenWidth - MeasureText("- Gustavo Vituri", 22)) / 2, 650, 22, Fade(GRAY, fadeAlpha));

    DrawText("Confira os assets em:", (screenWidth - MeasureText("Confira os assets em:", 18)) / 2, 710, 18, Fade(GRAY, fadeAlpha));
    DrawText("https://gvituri.itch.io/space-shooter", (screenWidth - MeasureText("https://gvituri.itch.io/space-shooter", 18)) / 2, 740, 18, Fade(LIGHTBLUE, fadeAlpha));

    DrawText("Pressione ENTER ou A para voltar ao menu", (screenWidth - MeasureText("Pressione ENTER ou A para voltar ao menu", 22)) / 2, 800, 22, Fade(LIGHTGRAY, fadeAlpha));

    EndDrawing();
}
