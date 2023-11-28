#include "Ball.h"


void Ball::Load() {
  x = GetScreenWidth() / 2.0f;
  y = GetScreenHeight() / 2.0f;
}

void Ball::Update(Sound& collisionSound) {
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

void Ball::Draw() {
  DrawCircle((int)x, (int)y, radius, ORANGE);
}

void Ball::CheckWinner(int& score1, int& score2) {
  if (x + radius >= GetScreenWidth()) {
    score1++;
    Reset();
  }

  if (x - radius <= 0) {
    score2++;
    Reset();
  }
}

void Ball::Reset() {
  x = GetScreenWidth() / 2.0f;
  y = GetScreenHeight() / 2.0f;

  int speed_choices[2] = { -1, 1 };
  speed_x *= speed_choices[GetRandomValue(0, 1)];
  speed_y *= speed_choices[GetRandomValue(0, 1)];
}
