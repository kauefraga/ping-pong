#include "game.h"

int main() {
  InitWindow(screen::WIDTH, screen::HEIGHT, "Ping Pong");
  InitAudioDevice();
  SetExitKey(KEY_NULL); // Disable ESC exiting
  SetTargetFPS(60);

  Image icon = LoadImage("resources/icon.png");
  SetWindowIcon(icon);
  UnloadImage(icon);

  Sound BallPaddleCollision = LoadSound("resources/sounds/ball-paddle.ogg");
  Sound BallTableCollision = LoadSound("resources/sounds/ball-table.ogg");

  Paddle player{};
  player.x = 10;
  player.y = (GetScreenHeight() / 2.0f) - (player.height / 2.0f);

  CpuPaddle computer{};
  computer.x = GetScreenWidth() - (computer.width + 10.0f);
  computer.y = (GetScreenHeight() / 2.0f) - (computer.height / 2.0f);

  Ball ball{};

  int player_score = 0;
  int computer_score = 0;

  while (!WindowShouldClose()) {

    if (IsKeyDown(KEY_S)) {
      player.y += player.speed;
    }

    if (IsKeyDown(KEY_W)) {
      player.y -= player.speed;
    }

    player.update();
    computer.update(ball.y);
    ball.update(BallTableCollision);
    ball.checkWinner(player_score, computer_score);

    if (CheckCollisionCircleRec(
      Vector2{ ball.x, ball.y },
      ball.radius,
      Rectangle{ player.x, player.y, (float) player.width, (float) player.height }
    )) {
      PlaySound(BallPaddleCollision);
      ball.speed_x *= -1;
    }

    if (CheckCollisionCircleRec(
      Vector2{ ball.x, ball.y },
      ball.radius,
      Rectangle{ computer.x, computer.y, (float) computer.width, (float) computer.height }
    )) {
      PlaySound(BallPaddleCollision);
      ball.speed_x *= -1;
    }

    BeginDrawing();

    ClearBackground(Color{ 42, 42, 42, 255 });

    DrawLine(
      GetScreenWidth() / 2,
      0,
      GetScreenWidth() / 2,
      GetScreenHeight(),
      RAYWHITE
    );

    player.draw();
    computer.draw();
    ball.draw();

    DrawText(TextFormat("%i", player_score), GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
    DrawText(TextFormat("%i", computer_score), 3 * GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);

    EndDrawing();
  }

  UnloadSound(BallPaddleCollision);
  UnloadSound(BallTableCollision);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
