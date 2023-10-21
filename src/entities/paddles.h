#pragma once

#include <raylib.h>
#include "entity.h"


class Paddle : public Entity {
protected:
  void LimitMovement() {
    if (y + height >= GetScreenHeight()) {
      y = (float)GetScreenHeight() - height;
    }

    if (y <= 0) {
      y = 0;
    }
  }

public:
  int speed = 10;
  int width = 20;
  int height = 100;

  void draw() {
    DrawRectangle((int)x, (int)y, width, height, RAYWHITE);
  }

  void update() {
    LimitMovement();
  }
};

class CpuPaddle : public Paddle {
public:
  void update(float ball_y) {
    if (y + height / 2.0f > ball_y) {
      y -= speed;
    }

    if (y + height / 2.0f <= ball_y) {
      y += speed;
    }

    LimitMovement();
  }
};
