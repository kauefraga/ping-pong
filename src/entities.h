#pragma once

#include <raylib.h>

class Ball {
public:
  float x = GetScreenWidth() / 2.0f;
  float y = GetScreenHeight() / 2.0f;
  int speed_x = 10;
  int speed_y = 5;
  float radius = 20;

  void draw() {
    DrawCircle((int)x, (int)y, radius, RAYWHITE);
  }

  void update(Sound& collisionSound) {
    x += speed_x;
    y += speed_y;

    if (x + radius >= GetScreenWidth() || x - radius <= 0) {
      PlaySound(collisionSound);
      speed_x *= -1;
    }

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
      PlaySound(collisionSound);
      speed_y *= -1;
    }
  }

  void checkWinner(int& score1, int& score2) {
    if (x + radius >= GetScreenWidth()) {
      score1++;
      reset();
    }

    if (x - radius <= 0) {
      score2++;
      reset();
    }
  }

  void reset() {
    x = GetScreenWidth() / 2.0f;
    y = GetScreenHeight() / 2.0f;

    int speed_choices[2] = { -1, 1 };
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
  }
};

class Paddle {
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
  float x;
  float y;
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
