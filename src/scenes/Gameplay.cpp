#include "Gameplay.h"


void GameplayScene::Load() {
  BallPaddleCollision = LoadSound("resources/sounds/ball-paddle.ogg");
  BallTableCollision = LoadSound("resources/sounds/ball-table.ogg");

  player = Paddle();
  player.x = 10;
  player.y = (GetScreenHeight() / 2.0f) - (player.height / 2.0f);

  player2 = Paddle();
  player2.x = GetScreenWidth() - (player2.width + 10.0f);
  player2.y = (GetScreenHeight() / 2.0f) - (player2.height / 2.0f);

  computer = CpuPaddle();
  computer.x = GetScreenWidth() - (computer.width + 10.0f);
  computer.y = (GetScreenHeight() / 2.0f) - (computer.height / 2.0f);

  ball = Ball();

  player_score = 0;
  player2_score = 0;
  computer_score = 0;
}

void GameplayScene::Unload() {
  UnloadSound(BallPaddleCollision);
  UnloadSound(BallTableCollision);
}

void GameplayScene::Update(int& currentScene, int& currentGameMode) {
  switch (currentGameMode) {
  case 0: {
    if (IsKeyDown(KEY_S)) {
      player.y += player.speed;
    }

    if (IsKeyDown(KEY_W)) {
      player.y -= player.speed;
    }

    player.Update();
    computer.Update(ball.y);
    ball.Update(BallTableCollision);
    ball.CheckWinner(player_score, computer_score);

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
  case 1: {
    if (IsKeyDown(KEY_S)) {
      player.y += player.speed;
    }

    if (IsKeyDown(KEY_W)) {
      player.y -= player.speed;
    }

    if (IsKeyDown(KEY_DOWN)) {
      player2.y += player2.speed;
    }

    if (IsKeyDown(KEY_UP)) {
      player2.y -= player2.speed;
    }

    player.Update();
    player2.Update();
    ball.Update(BallTableCollision);
    ball.CheckWinner(player_score, player2_score);

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
      Rectangle{ player2.x, player2.y, (float)player2.width, (float)player2.height }
    )) {
      PlaySound(BallPaddleCollision);
      ball.speed_x *= -1;
    }
  } break;
  }
}

void GameplayScene::Render(int& currentGameMode) {
  switch (currentGameMode) {
  case 0: {
    DrawLine(
      GetScreenWidth() / 2,
      0,
      GetScreenWidth() / 2,
      GetScreenHeight(),
      RAYWHITE
    );

    player.Draw();
    computer.Draw();
    ball.Draw();

    DrawText(TextFormat("%i", player_score), GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
    DrawText(TextFormat("%i", computer_score), 3 * GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
  } break;
  case 1: {
    DrawLine(
      GetScreenWidth() / 2,
      0,
      GetScreenWidth() / 2,
      GetScreenHeight(),
      RAYWHITE
    );

    player.Draw();
    player2.Draw();
    ball.Draw();

    DrawText(TextFormat("%i", player_score), GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
    DrawText(TextFormat("%i", player2_score), 3 * GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
  } break;
  }
}
