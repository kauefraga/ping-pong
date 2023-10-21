#pragma once

namespace screen {
  const int WIDTH = 1280;
  const int HEIGHT = 720;
}

typedef enum GameScene { LOGO = 0, SELECT_GAME_MODE, GAMEPLAY } GameScene;
typedef enum GameMode { PLAYER_VERSUS_CPU = 0, PLAYER_VERSUS_PLAYER } GameMode;
