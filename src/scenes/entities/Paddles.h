#pragma once

#include <raylib.h>
#include "entity.h"


class Paddle : public Entity {
protected:
  void LimitMovement();
public:
  int speed = 10;
  int width = 20;
  int height = 100;

  void Update();
  void Draw();
};

class CpuPaddle : public Paddle {
public:
  void Update(const float& ball_y);
};
