#pragma once

#include <raylib.h>
#include "scenes/sounds/Music.h"
#include "scenes/Start.h"
#include "scenes/Gamemode.h"
#include "scenes/Gameplay.h"


class Game {
private:
  const int SCREEN_WIDTH = 1280;
  const int SCREEN_HEIGHT = 720;

  Music soundTrack;
  float timePlayed = 0.0f;
  bool pauseMusic;

  // START = 0, SELECT_GAME_MODE = 1, GAMEPLAY = 2
  int currentScene;
  // PLAYER_VS_CPU = 0, PLAYER_VS_PLAYER
  int currentGameMode;

  StartScene startScene;
  GamemodeScene gamemodeScene;
  GameplayScene gameplayScene;
public:
  Game();

  // Resources management
  void InitializeWindow();
  void LoadResources();
  void UnloadAndClose();

  // Update and render game
  void Update();
  void Render();

  bool IsRunning();
};

