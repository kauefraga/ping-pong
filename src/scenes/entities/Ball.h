#pragma once

#include <raylib.h>
#include "Entity.h"


class Ball : public Entity {
public:
  int speed_x = 10;
  int speed_y = 5;
  float radius = 20;

  void Load();

  void Update(Sound& collisionSound);
  void Draw();

  void CheckWinner(int& score1, int& score2);
  void Reset();
};
