#include "game.h"

using namespace palette;

int main() {
  InitWindow(screen::WIDTH, screen::HEIGHT, "Ping Pong"); // Initialize the window and opengl context

  SetExitKey(KEY_NULL);

  SetTargetFPS(60);

  Image icon = LoadImage("resources/icon.png");

  SetWindowIcon(icon);

  UnloadImage(icon);

  Texture layout = LoadTexture("resources/layout.png");

  int left_score = 0;
  int right_score = 0;

  Paddle left{
    (GetScreenWidth() / 2.0f) - (table::WIDTH / 2) + PADDLE_PADDING
  };

  Paddle right{
    (GetScreenWidth() / 2.0f) + (table::WIDTH / 2) - PADDLE_PADDING - 5 // 5 is border correction
  };

  Ball ball{};

  // If ESC is pressed the game closes
  while (!WindowShouldClose()) {
    /* --- UPDATE --- */

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

    ball.x += ball.speed_x * GetFrameTime();
    ball.y += ball.speed_y * GetFrameTime();

    if (ball.speed_x > 2500) {
      ball.speed_x = 300;
    }

    /* --- COLLISIONS paddle-ball --- */
    // left paddle-ball collision
    if (CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { left.x, left.y, left.width, left.height }
    )) {
      if (ball.speed_x < 0) {
        ball.speed_x *= -1.05f;
        ball.speed_y = (ball.y - left.y);
        // SEE: https://gamedev.stackexchange.com/questions/4253/in-pong-how-do-you-calculate-the-balls-direction-when-it-bounces-off-the-paddl
      }
    }

    // right paddle-ball collision
    if (CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { right.x, right.y, right.width, right.height }
    )) {
      if (ball.speed_x > 0) {
        ball.speed_x *= -1.05f;
        ball.speed_y = (ball.y - right.y);
      }
    }

    // ball limits
    bool ball_ceil_limit = CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { table::OFFSET_X, table::OFFSET_Y, table::WIDTH, 1 }
    );

    bool ball_floor_limit = CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { table::OFFSET_X, table::HEIGHT + table::OFFSET_Y - 20, table::WIDTH, 1 } // -20 is border correction
    );

    bool ball_left_limit = CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { table::OFFSET_X, table::OFFSET_Y, 1, table::HEIGHT }
    );

    bool ball_right_limit = CheckCollisionCircleRec(
      { ball.x, ball.y },
      ball.radius,
      { table::WIDTH + table::OFFSET_X - 15, table::OFFSET_Y, 1, table::HEIGHT } // -15 is border correction
    );

    if (ball_ceil_limit) {
      ball.speed_y *= -1;
    }

    if (ball_floor_limit) {
      ball.speed_y *= -1;
    }

    if (ball_left_limit) {
      ball.reset();
      ball.speed_x += ball.speed_x * GetFrameTime();
      ball.speed_y += ball.speed_y * GetFrameTime();
      right_score += 1 ; // if the ball touches the left wall, right paddle points
    }

    if (ball_right_limit) {
      ball.reset();
      ball.speed_x += ball.speed_x * GetFrameTime();
      ball.speed_y += ball.speed_y * GetFrameTime();
      left_score += 1; // if the ball toucher the right wall, left paddle points
    }

    if (IsKeyReleased(KEY_R)) {
      ball.reset();
    }

    /* --- DRAW --- */
    BeginDrawing();

    // Clear the screen before start drawing
    ClearBackground(RAYWHITE);

    // Table, players icon and scoreboard
    DrawTexture(layout, 0, 0, WHITE);

    // Score board
    DrawText(TextFormat("%ix%i", left_score, right_score),
      (screen::WIDTH - MeasureText("XxX", 50)) / 2,
      screen::SCORE_OFFSET_Y,
      50,
      ODD_PURPLE
    );

    // left paddle
    left.draw();

    // right paddle
    right.draw();

    // Ball
    ball.draw();

    EndDrawing();
  }

  UnloadTexture(layout);

  CloseWindow();

  return 0;
}
