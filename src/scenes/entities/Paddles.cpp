#include "Paddles.h"


void Paddle::Load(const float x, const float y) {
  Entity::x = x;
  Entity::y = y;
}

void Paddle::Update() {
  LimitMovement();
}

void Paddle::Draw() {
  DrawRectangle((int)x, (int)y, width, height, RAYWHITE);
}

void Paddle::LimitMovement() {
  if (y + height >= GetScreenHeight()) {
    y = (float)GetScreenHeight() - height;
  }

  if (y <= 0) {
    y = 0;
  }
}

void Paddle::UpdateCpu(const float& ball_y) {
  if (y + height / 2.0f > ball_y) {
    y -= speed;
  }

  if (y + height / 2.0f <= ball_y) {
    y += speed;
  }

  LimitMovement();
}

Rectangle Paddle::GetRect() {
  return Rectangle{ x, y, (float) width, (float) height };
}
