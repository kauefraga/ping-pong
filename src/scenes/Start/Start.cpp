#include "Start.h"


void StartScene::Load() {

}

void StartScene::Unload() {

}

void StartScene::Update(int& currentScene) {
  if (IsKeyDown(KEY_SPACE)) {
    currentScene = 1;
  }
}

void StartScene::Render() {
  DrawText(
    "Ping Pong",
    (GetScreenWidth() / 2) - (MeasureText("Ping Pong", 120) / 2),
    GetScreenHeight() / 3,
    120,
    Color{ 199, 14, 14, 255 }
  );

  DrawText(
    "Press SPACE to start",
    (GetScreenWidth() / 2) - (MeasureText("Press SPACE to start", 60) / 2),
    (int)(GetScreenHeight() / 1.5f),
    60,
    RAYWHITE
  );
}
