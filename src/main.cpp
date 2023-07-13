#include "game.h"

using namespace palette;

int main() {
  InitWindow(screen::WIDTH, screen::HEIGHT, "Ping Pong"); // Initialize the window and opengl context

  Image icon = LoadImage("resources/icon.png"); // Load image in memory

  SetWindowIcon(icon);

  UnloadImage(icon); // Free the image (optimization)

  Texture background = LoadTexture("resources/background-pixel.png"); // Load the table

  int left_score = 0;
  int right_score = 0;

  Paddle left{
    (GetScreenWidth() / 2.0f) - (table::WIDTH / 2) + 20, // 20 is a padding
    GetScreenHeight() / 2.0f
  };

  Paddle right{
    (GetScreenWidth() / 2.0f) + (table::WIDTH / 2) - 20, // -20 is a padding
    GetScreenHeight() / 2.0f
  };

  Ball ball{};

  SetTargetFPS(60);

  // If ESC is pressed the game closes
  while (!WindowShouldClose()) {
    /* --- UPDATE --- */

    ball.x += ball.speed_x * GetFrameTime();
    ball.y += ball.speed_y * GetFrameTime();

    // ball limits
    bool ball_ceil_limit = CheckCollisionCircleRec({ ball.x, ball.y },
      ball.radius, { table::OFFSET_X, table::OFFSET_Y, table::WIDTH, 1 });

    bool ball_floor_limit = CheckCollisionCircleRec({ ball.x, ball.y },
      ball.radius, { table::OFFSET_X, table::HEIGHT + table::OFFSET_Y, table::WIDTH, 1 });

    bool ball_left_limit = CheckCollisionCircleRec({ ball.x, ball.y },
      ball.radius, { table::OFFSET_X, table::OFFSET_Y, 1, table::HEIGHT });

    bool ball_right_limit = CheckCollisionCircleRec({ ball.x, ball.y },
      ball.radius, { table::WIDTH + table::OFFSET_X, table::OFFSET_Y, 1, table::HEIGHT });

    if (ball_ceil_limit) {
      ball.speed_y *= -1;
    }

    if (ball_floor_limit) {
      ball.speed_y *= -1;
    }

    if (ball_left_limit) {
      ball.speed_x *= -1;
      right_score += 1; // if the ball touches the left wall, right paddle points
    }

    if (ball_right_limit) {
      ball.speed_x *= -1;
      left_score += 1; // if the ball toucher the right wall, left paddle points
    }

    // left paddle (wasd)
    if (IsKeyDown(KEY_S)) {
      left.y += PADDLE_SPEED * GetFrameTime();
    }

    if (IsKeyDown(KEY_W)) {
      left.y -= PADDLE_SPEED * GetFrameTime();
    }

    // right paddle (arrows)
    if (IsKeyDown(KEY_DOWN)) {
      right.y += PADDLE_SPEED * GetFrameTime();
    }

    if (IsKeyDown(KEY_UP)) {
      right.y -= PADDLE_SPEED * GetFrameTime();
    }

    /* --- COLLISIONS paddle-BALL --- */
    // left paddle-ball collision
    if (CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { left.x, left.y, left.width, left.height }
    )) {
      if (ball.speed_x < 0) {
        ball.speed_x *= -1.1f;
        ball.speed_y = (ball.y - left.y);
      }
    }

    // right paddle-ball collision
    if (CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { right.x, right.y, right.width, right.height }
    )) {
      if (ball.speed_x < 0) {
        ball.speed_x *= -1.1f;
        ball.speed_y = (ball.y - right.y);
      }
    }

    /* --- DRAW --- */
    BeginDrawing();

    // Clear the screen before start drawing
    ClearBackground(RAYWHITE);

    // Table
    DrawTexture(background, 0, 0, WHITE);

    // Score board
    DrawText(TextFormat("%ix%i", left_score, right_score),
      (screen::WIDTH / 2) - (MeasureText("xxx", 50) / 2),
      35,
      50,
      ODD_PURPLE
    );

    // left paddle
    left.draw();

    // right paddle
    right.draw();

    // Ball
    ball.draw();

    DrawFPS(50, 50);

    EndDrawing();
  }

  // Unload background texture
  UnloadTexture(background);

  // Close window and unload opengl context
  CloseWindow();

  return 0;
}
