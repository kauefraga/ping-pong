#pragma once
#include <raylib.h>

/* ----- SCREEN ----- */
namespace screen {
  const int WIDTH = 1000;
  const int HEIGHT = 700;

  // FPS limit vs. Vsync
}

/* ----- TABLE ----- */
namespace table {
  const int WIDTH = 900;
  const int HEIGHT = 500;

  // The distance between the top to table-top and left to table-left
  const int OFFSET_X = 50;
  const int OFFSET_Y = 145;
}

/* ----- PADDLE ----- */
const int PADDLE_SPEED = 500;

struct Paddle {
  float x;
  float y;
  float width = 5;
  float height = 50;

  void draw() {
    DrawRectangle((int) x, (int) y, (int) width, (int) height, BLACK);
  }
};

/* ----- BALL ----- */
struct Ball {
  float x = GetScreenWidth() / 2.0f;
  float y = GetScreenHeight() / 2.0f;
  float speed_x = 300.0f;
  float speed_y = 150.0f;
  float radius = 15;
   
  void draw() {
    DrawCircle((int) x, (int) y, radius, WHITE);
  }
};

/* ----- PALETTE -----
 * OOD FEELING PALETTE
 * Creator: XENO
 * See: https://lospec.com/palette-list/odd-feeling
*/
namespace palette {
  const Color ODD_PURPLE{ 144, 12, 63, 255 };
}
