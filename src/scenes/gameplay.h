#pragma once

#include <raylib.h>
#include "entities/Paddles.h"
#include "entities/Ball.h"


class GameplayScene {
private:
  Sound BallPaddleCollision;
  Sound BallTableCollision;

  Paddle player;
  Paddle player2;
  CpuPaddle computer;
  Ball ball;

  int player_score;
  int player2_score;
  int computer_score;
public:
  void Load();
  void Unload();
  void Update(int& currentScene, int& currentGameMode);
  void Render(int& currentGameMode);
};
