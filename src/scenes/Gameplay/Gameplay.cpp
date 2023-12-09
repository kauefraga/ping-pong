#include "Gameplay.h"


void GameplayScene::Load() {
  BallPaddleCollision = LoadSound("resources/sounds/ball-paddle.ogg");
  BallTableCollision = LoadSound("resources/sounds/ball-table.ogg");

  player.Load(
    10,
    (GetScreenHeight() / 2.0f) - (player.height / 2.0f)
  );

  player2.Load(
    GetScreenWidth() - (player2.width + 10.0f),
    (GetScreenHeight() / 2.0f) - (player2.height / 2.0f)
  );      

  ball.Load();

  score1 = 0;
  score2 = 0;
}

void GameplayScene::Unload() {
  UnloadSound(BallPaddleCollision);
  UnloadSound(BallTableCollision);
}

void GameplayScene::Update(int& currentScene, int& currentGameMode) {
  if (IsKeyDown(KEY_S)) {
    player.y += player.speed;
  }

  if (IsKeyDown(KEY_W)) {
    player.y -= player.speed;
  }

  if (currentGameMode == 0) {
    player.Update();
    player2.UpdateCpu(ball.y);
    ball.Update(BallTableCollision);
    ball.CheckWinner(score1, score2);

    if (CheckCollisionCircleRec(
      Vector2{ ball.x, ball.y },
      ball.radius,
      player.GetRect()
    )) {
      PlaySound(BallPaddleCollision);
      ball.speed_x *= -1;
    }

    if (CheckCollisionCircleRec(
      Vector2{ ball.x, ball.y },
      ball.radius,
      player2.GetRect()
    )) {
      PlaySound(BallPaddleCollision);
      ball.speed_x *= -1;
    }
  }

  if (currentGameMode == 1) {
    if (IsKeyDown(KEY_DOWN)) {
      player2.y += player2.speed;
    }

    if (IsKeyDown(KEY_UP)) {
      player2.y -= player2.speed;
    }

    player.Update();
    player2.Update();
    ball.Update(BallTableCollision);
    ball.CheckWinner(score1, score2);

    if (CheckCollisionCircleRec(
      Vector2{ ball.x, ball.y },
      ball.radius,
      player.GetRect()
    )) {
      PlaySound(BallPaddleCollision);
      ball.speed_x *= -1;
    }

    if (CheckCollisionCircleRec(
      Vector2{ ball.x, ball.y },
      ball.radius,
      player2.GetRect()
    )) {
      PlaySound(BallPaddleCollision);
      ball.speed_x *= -1;
    }
  }
}

void GameplayScene::Render() {
  DrawLine(
    GetScreenWidth() / 2,
    0,
    GetScreenWidth() / 2,
    GetScreenHeight(),
    RAYWHITE
  );

  DrawText(TextFormat("%i", score1), GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
  DrawText(TextFormat("%i", score2), 3 * GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);

  player.Draw();
  player2.Draw();
  ball.Draw();
}
