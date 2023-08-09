#pragma once

#include <raylib.h>

/* ----- SCREEN ----- */
namespace screen {
  const int WIDTH = 1000;
  const int HEIGHT = 700;

  // The distance between the top to score origin.
  const int SCORE_OFFSET_Y = 80;
}

/* ----- TABLE ----- */
namespace table {
  const int WIDTH = 920;
  const int HEIGHT = 440;

  // The distance between the top to table-top and left to table-left.
  const int OFFSET_X = 50;
  const int OFFSET_Y = 230;
}

/* ----- PADDLE ----- */
const int PADDLE_SPEED = 500;
const int PADDLE_PADDING = 30;

struct Paddle {
  float x;
  float y = (GetScreenHeight() / 2.0f) + (table::HEIGHT / 2.0f - table::OFFSET_Y / 2.0f) - 50; // 50 is the paddle height
  float width = 5;
  float height = 50;

  void draw() {
    DrawRectangle((int) x, (int) y, (int) width, (int) height, BLACK);
  }
};

/* ----- BALL ----- */
struct Ball {
  float x = GetScreenWidth() / 2.0f;
  float y = (GetScreenHeight() / 2.0f) + (table::HEIGHT / 2.0f - table::OFFSET_Y / 2.0f) - 30; // 30 is the diameter of the ball
  float speed_x = 300.0f;
  float speed_y = 150.0f;
  float radius = 15;

  void draw() {
    DrawCircle((int) x, (int) y, radius, WHITE);
  }

  void reset() {
    x = GetScreenWidth() / 2.0f;
    y = (GetScreenHeight() / 2.0f) + (table::HEIGHT / 2.0f - table::OFFSET_Y / 2.0f);
    speed_x = 300.0f;
    speed_y = 150.0f;
  }
};

/* ----- OOD FEELING PALETTE -----
 * Creator: XENO
 * See: https://lospec.com/palette-list/odd-feeling
*/
namespace palette {
  const Color ODD_PURPLE{ 144, 12, 63, 255 };
}
