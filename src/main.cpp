#include <raylib.h>
#include "entities.h"

const int WIDTH = 1000;
const int HEIGHT = 700;
const int TABLE_WIDTH = 900;
const int TABLE_HEIGHT = 500;

int main() {
  InitWindow(WIDTH, HEIGHT, "Ping Pong"); // Initialize the window and opengl context

  Image icon = LoadImage("resources/icon.png"); // Load image in memory

  SetWindowIcon(icon);

  UnloadImage(icon); // Free the image (optimization)

  int first_score = 0;
  int second_score = 0;

  Vector2 first_racket{ (WIDTH / 2) - (TABLE_WIDTH / 2) + 20, HEIGHT / 2 };
  Vector2 second_racket{ (WIDTH / 2) + (TABLE_WIDTH / 2) - 20, HEIGHT / 2 };
  Vector2 ball_position{ WIDTH / 2, HEIGHT / 2 };
  Vector2 ball_speed{ 5, 0 };

  SetTargetFPS(60);

  // If ESC is pressed the game closes
  while (!WindowShouldClose()) {
    /* --- UPDATE --- */
    // first racket (wasd)
    if (IsKeyDown(KEY_S)) {
      bool first_racket_floor_limit = CheckCollisionRecs(
        { first_racket.x, first_racket.y, 5, 50 }, { 50, TABLE_HEIGHT + 120 - 5, TABLE_WIDTH, 1 }
      );

      first_racket_floor_limit ? first_racket.y : first_racket.y += 5;
    }

    if (IsKeyDown(KEY_W)) {
      bool first_racket_ceil_limit = CheckCollisionRecs(
        { first_racket.x, first_racket.y, 5, 50 }, { 50, 120, TABLE_WIDTH, 1 }
      );

      first_racket_ceil_limit ? first_racket.y : first_racket.y -= 5;
    }

    // second racket (arrows)
    if (IsKeyDown(KEY_DOWN)) {
      bool second_racket_floor_limit = CheckCollisionRecs(
        { second_racket.x, second_racket.y, 5, 50 }, { 50, TABLE_HEIGHT + 120 - 5, TABLE_WIDTH, 1 }
      );

      second_racket_floor_limit ? second_racket.y : second_racket.y += 5;
    }

    if (IsKeyDown(KEY_UP)) {
      bool second_racket_ceil_limit = CheckCollisionRecs(
        { second_racket.x, second_racket.y, 5, 50 }, { 50, 120, TABLE_WIDTH, 1 }
      );

      second_racket_ceil_limit ? second_racket.y : second_racket.y -= 5;
    }

    /* --- COLLISIONS RACKET-BALL --- */
    // first racket-ball collision
    bool first_racket_collision = CheckCollisionCircleRec(ball_position, 20, { first_racket.x, first_racket.y, 3, 50 });
    if (first_racket_collision) {
      ball_speed.x = 5;
      ball_speed.y = (float)GetRandomValue(-2, 2);
    }

    // second racket-ball collision
    bool second_racket_collision = CheckCollisionCircleRec(ball_position, 20, { second_racket.x, second_racket.y, 3, 50 });
    if (second_racket_collision) {
      ball_speed.x = -5;
      ball_speed.y = (float)GetRandomValue(-2, 2);
    }

    // ball limits
    bool ball_ceil_limit = CheckCollisionCircleRec(ball_position,
      20, { 50, 120, TABLE_WIDTH, 1 });

    bool ball_floor_limit = CheckCollisionCircleRec(ball_position,
      20, { 50, TABLE_HEIGHT + 120, TABLE_WIDTH, 1 });

    bool ball_left_limit = CheckCollisionCircleRec(ball_position,
      20, { 50, 120, 1, TABLE_HEIGHT });

    bool ball_right_limit = CheckCollisionCircleRec(ball_position,
      20, { TABLE_WIDTH + 50, 120, 1, TABLE_HEIGHT });

    if (ball_ceil_limit) ball_speed.y = 1;
    if (ball_floor_limit) ball_speed.y = -1;
    if (ball_left_limit) {
      ball_speed.x = 5;
      second_score += 1; // if the ball touches the left wall, second racket points
    }
    if (ball_right_limit) {
      ball_speed.x = -5;
      first_score += 1; // if the ball toucher the right wall, first racket points
    }

    ball_position.x += ball_speed.x;
    ball_position.y += ball_speed.y;

    /* --- DRAW --- */
    BeginDrawing();

    ClearBackground(BLACK); // Clear the screen before draw stuff

    DrawText(TextFormat("%ix%i", first_score, second_score),
      (WIDTH / 2) - (MeasureText("xxx", 30) / 2),
      30,
      30,
      GREEN
    );

    // Table
    DrawRectangle(50, 120, TABLE_WIDTH, TABLE_HEIGHT, PINK);

    // First racket
    DrawRectangleV(first_racket, { 5, 50 }, RAYWHITE);

    // Second racket
    DrawRectangleV(second_racket, { 5, 50 }, RAYWHITE);

    // Ball
    DrawCircleV(ball_position, 20, BLUE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
