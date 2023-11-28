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

  void Load(const float x, const float y);
  void Update();
  void UpdateCpu(const float& ball_y);
  void Draw();

  Rectangle GetRect();
};
