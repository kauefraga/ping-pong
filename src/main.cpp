#include "constants.h"
#include "scenes/start.h"
#include "scenes/gamemode.h"
#include "scenes/gameplay.h"


GameScene currentScene;
GameMode currentGameMode;

StartScene startScene;
GamemodeScene gamemodeScene;
GameplayScene gameplayScene;

void init() {
  InitWindow(screen::WIDTH, screen::HEIGHT, "Ping Pong");
  InitAudioDevice();
  SetExitKey(KEY_NULL); // Disable ESC exiting
  SetTargetFPS(60);

  Image icon = LoadImage("resources/icon.png");
  SetWindowIcon(icon);
  UnloadImage(icon);

  currentScene = LOGO;
  currentGameMode = PLAYER_VERSUS_CPU;

  startScene = StartScene();
  gamemodeScene = GamemodeScene();
  gameplayScene = GameplayScene();

  startScene.load();
  gamemodeScene.load();
  gameplayScene.load();
}

void quit() {
  startScene.unload();
  gamemodeScene.unload();
  gameplayScene.unload();

  CloseAudioDevice();
  CloseWindow();
}

int main() {
  init();

  while (!WindowShouldClose()) {
    switch (currentScene) {
    case LOGO: {
      startScene.update(currentScene);
    } break;
    case SELECT_GAME_MODE: {
      gamemodeScene.update(currentScene, currentGameMode);
    } break;
    case GAMEPLAY: {
      gameplayScene.update(currentScene, currentGameMode);
    } break;
    default: break; // Loading screen
    }

    BeginDrawing();
    ClearBackground(Color{ 42, 42, 42, 255 });

    switch (currentScene) {
    case LOGO: {
      startScene.render();
    } break;
    case SELECT_GAME_MODE: {
      gamemodeScene.render(currentGameMode);
    } break;
    case GAMEPLAY: {
      gameplayScene.render(currentGameMode);
    } break;
    default: break;
    }

    EndDrawing();
  }

  quit();

  return 0;
}
