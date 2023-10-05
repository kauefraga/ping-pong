#include "game.h"


typedef enum GameScreen { LOGO = 0, SELECT_GAME_MODE, GAMEPLAY } GameScreen;
typedef enum GameMode { PLAYER_VERSUS_CPU = 0, PLAYER_VERSUS_PLAYER } GameMode;

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

  GameScreen currentScreen = LOGO;
  GameMode currentGameMode = PLAYER_VERSUS_CPU;

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
    switch (currentScreen) {
      case LOGO: {
        if (IsKeyDown(GetKeyPressed())) {
          currentScreen = GAMEPLAY;
        }
      } break;
      case SELECT_GAME_MODE: {} break;
      case GAMEPLAY: {
        switch (currentGameMode) {
          case PLAYER_VERSUS_CPU: {
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
              Rectangle{ player.x, player.y, (float)player.width, (float)player.height }
            )) {
              PlaySound(BallPaddleCollision);
              ball.speed_x *= -1;
            }

            if (CheckCollisionCircleRec(
              Vector2{ ball.x, ball.y },
              ball.radius,
              Rectangle{ computer.x, computer.y, (float)computer.width, (float)computer.height }
            )) {
              PlaySound(BallPaddleCollision);
              ball.speed_x *= -1;
            }
          } break;
          case PLAYER_VERSUS_PLAYER: {} break;
          default: break;
        }
      } break;
      default: break;
    }

    BeginDrawing();

    ClearBackground(Color{ 42, 42, 42, 255 });

    switch (currentScreen) {
      case LOGO: {
        DrawText(
          "Ping Pong",
          (GetScreenWidth() / 2) - (MeasureText("Ping Pong", 120) / 2),
          GetScreenHeight() / 3,
          120,
          Color{ 199, 14, 14, 255 }
        );

        DrawText(
          "Press any key to start",
          (GetScreenWidth() / 2) - (MeasureText("Press any key to start", 60) / 2),
          (int) (GetScreenHeight() / 1.5f),
          60,
          RAYWHITE
        );
      } break;
      case SELECT_GAME_MODE: {} break;
      case GAMEPLAY: {
        switch (currentGameMode) {
          case PLAYER_VERSUS_CPU: {
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
          } break;
          case PLAYER_VERSUS_PLAYER: {} break;
          default: break;
        }
      } break;
      default: break;
    }

    EndDrawing();
  }

  UnloadSound(BallPaddleCollision);
  UnloadSound(BallTableCollision);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}
