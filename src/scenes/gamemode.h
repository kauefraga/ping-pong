#pragma once

#include <raylib.h>


class GamemodeScene {
public:

  void load() {

  }

  void unload() {

  }

  void update(GameScene &currentScene, GameMode &currentGameMode) {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
      currentGameMode = PLAYER_VERSUS_CPU;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
      currentGameMode = PLAYER_VERSUS_PLAYER;
    }

    if (IsKeyDown(KEY_ENTER)) {
      currentScene = GAMEPLAY;
    }
  }

  void render(GameMode &currentGameMode) {
    DrawText(
      "Select game mode",
      (GetScreenWidth() / 2) - (MeasureText("Select game mode", 60) / 2),
      GetScreenHeight() / 5,
      60,
      RAYWHITE
    );

    // Hovering effect
    if (currentGameMode == 0) {
      DrawText(
        "* Player Vs. CPU",
        (GetScreenWidth() / 2) - (MeasureText("* Player Vs. CPU", 50) / 2),
        (int)(GetScreenHeight() / 2.5f),
        50,
        SKYBLUE
      );
    }
    else {
      DrawText(
        "Player Vs. CPU",
        (GetScreenWidth() / 2) - (MeasureText("Player Vs. CPU", 50) / 2),
        (int)(GetScreenHeight() / 2.5f),
        50,
        RAYWHITE
      );
    }

    if (currentGameMode == 1) {
      DrawText(
        "* Player Vs. Player",
        (GetScreenWidth() / 2) - (MeasureText("* Player Vs. Player", 50) / 2),
        GetScreenHeight() / 2,
        50,
        SKYBLUE
      );
    }
    else {
      DrawText(
        "Player Vs. Player",
        (GetScreenWidth() / 2) - (MeasureText("Player Vs. Player", 50) / 2),
        GetScreenHeight() / 2,
        50,
        RAYWHITE
      );
    }

    DrawText(
      "Hit ENTER to start playing",
      (GetScreenWidth() / 2) - (MeasureText("Hit ENTER to start playing", 40) / 2),
      (int)(GetScreenHeight() / 1.2f),
      40,
      GRAY
    );
  }
};
