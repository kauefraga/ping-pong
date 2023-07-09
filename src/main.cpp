#include <raylib.h>

int main() {
  const int WIDTH = 600;
  const int HEIGHT = 600;

  InitWindow(WIDTH, HEIGHT, "Ping Pong");

  int first_score = 0;
  int second_score = 0;

  Vector2 first_racket{ 50, HEIGHT / 2 };
  Vector2 second_racket{ 550, HEIGHT / 2 };
  Vector2 ball_position{ WIDTH / 2, HEIGHT / 2 };
  Vector2 ball_speed{ 2, 0 };

  SetTargetFPS(60);

  // If ESC is pressed the game closes
  while (!WindowShouldClose()) {
    /* --- UPDATE --- */
    // first racket (wasd)
    if (IsKeyDown(KEY_S)) first_racket.y += 5;
    if (IsKeyDown(KEY_W)) first_racket.y -= 5;

    // second racket (arrows)
    if (IsKeyDown(KEY_DOWN)) second_racket.y += 5;
    if (IsKeyDown(KEY_UP)) second_racket.y -= 5;

    /* --- COLLISIONS --- */
    // screen limit
    // first racket
    bool first_racket_ceil_limit = CheckCollisionRecs(
      { first_racket.x, first_racket.y, 3, 50 }, { 0, 0, 600, 1 }
    );
    bool first_racket_floor_limit = CheckCollisionRecs(
      { first_racket.x, first_racket.y, 3, 50 }, { 0, 600, 600, 1 }
    );

    if (first_racket_ceil_limit) first_racket.y = 0;

    if (first_racket_floor_limit) first_racket.y = 550;

    // second racket
    bool second_racket_ceil_limit = CheckCollisionRecs(
      { second_racket.x, second_racket.y, 3, 50 }, { 0, 0, 600, 1 }
    );
    bool second_racket_floor_limit = CheckCollisionRecs(
      { second_racket.x, second_racket.y, 3, 50 }, { 0, 600, 600, 1 }
    );

    if (second_racket_ceil_limit) second_racket.y = 0;

    if (second_racket_floor_limit) second_racket.y = 550;

    // ball
    bool ball_ceil_limit = CheckCollisionCircleRec(ball_position, 20, { 0, 0, 600, 1 });
    bool ball_floor_limit = CheckCollisionCircleRec(ball_position, 20, { 0, 600, 600, 1 });
    bool ball_left_limit = CheckCollisionCircleRec(ball_position, 20, { 0, 0, 1, 600 });
    bool ball_right_limit = CheckCollisionCircleRec(ball_position, 20, { 600, 0, 1, 600 });

    if (ball_ceil_limit) ball_speed.y = 1;
    if (ball_floor_limit) ball_speed.y = -1;
    if (ball_left_limit) {
      ball_speed.x = 1;
      second_score += 1; // if the ball touches the left wall, second racket points
    }
    if (ball_right_limit) {
      ball_speed.x = -1;
      first_score += 1; // if the ball toucher the right wall, first racket points
    }

    // first racket
    bool first_racket_collision = CheckCollisionCircleRec(ball_position, 20, { first_racket.x, first_racket.y, 3, 50 });
    if (first_racket_collision) {
      ball_speed.x = 2;
      ball_speed.y = (float)GetRandomValue(-1, 1);
    }

    // second racket
    bool second_racket_collision = CheckCollisionCircleRec(ball_position, 20, { second_racket.x, second_racket.y, 3, 50 });
    if (second_racket_collision) {
      ball_speed.x = -2;
      ball_speed.y = (float)GetRandomValue(-1, 1);
    }

    /* --- DRAW --- */
    BeginDrawing();

    ClearBackground(BLACK); // Clear the screen before draw stuff

    DrawText("Bom Jogo!", 230, 0, 30, RED);
    DrawText(TextFormat("First score: %i", first_score), 30, 30, 35, GREEN);
    DrawText(TextFormat("Second score: %i", second_score), 30, 65, 35, GREEN);

    // First racket
    DrawRectangleV(first_racket, { 3, 50 }, RAYWHITE);

    // Second racket
    DrawRectangleV(second_racket, { 3, 50 }, RAYWHITE);

    // Ball
    DrawCircleV({ ball_position.x += ball_speed.x, ball_position.y += ball_speed.y }, 20, BLUE);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
