#pragma once

#include <raylib.h>
#include "../entities/Paddles.h"
#include "../entities/Ball.h"


class GameplayScene {
private:
  Sound BallPaddleCollision;
  Sound BallTableCollision;

  Paddle player;
  Paddle player2;
  Ball ball;

  int score1;
  int score2;
public:
  void Load();
  void Unload();
  void Update(int& currentScene, int& currentGameMode);
  void Render();
};
