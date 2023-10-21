#include "game.h"
#include "constants.h"


typedef enum GameScreen { LOGO = 0, SELECT_GAME_MODE, GAMEPLAY } GameScreen;
typedef enum GameMode { PLAYER_VERSUS_CPU = 0, PLAYER_VERSUS_PLAYER } GameMode;

GameScreen currentScreen;
GameMode currentGameMode;

Sound BallPaddleCollision;
Sound BallTableCollision;

Paddle player;
Paddle player2;
CpuPaddle computer;
Ball ball;

int player_score;
int player2_score;
int computer_score;

void update() {
  switch (currentScreen) {
  case LOGO: {
    if (IsKeyDown(KEY_SPACE)) {
      currentScreen = SELECT_GAME_MODE;
    }
  } break;
  case SELECT_GAME_MODE: {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
      currentGameMode = PLAYER_VERSUS_CPU;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
      currentGameMode = PLAYER_VERSUS_PLAYER;
    }

    if (IsKeyDown(KEY_ENTER)) {
      currentScreen = GAMEPLAY;
    }
  } break;
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
    case PLAYER_VERSUS_PLAYER: {
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

      player.update();
      player2.update();
      ball.update(BallTableCollision);
      ball.checkWinner(player_score, player2_score);

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
    default: break;
    }
  } break;
  default: break;
  }
}

void drawScene() {
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
      "Press SPACE to start",
      (GetScreenWidth() / 2) - (MeasureText("Press SPACE to start", 60) / 2),
      (int)(GetScreenHeight() / 1.5f),
      60,
      RAYWHITE
    );
  } break;
  case SELECT_GAME_MODE: {
    DrawText(
      "Select game mode",
      (GetScreenWidth() / 2) - (MeasureText("Select game mode", 60) / 2),
      GetScreenHeight() / 5,
      60,
      RAYWHITE
    );

    // Hovering effect
    if (currentGameMode == 0) {
      DrawText(
        "* Player Vs. CPU",
        (GetScreenWidth() / 2) - (MeasureText("* Player Vs. CPU", 50) / 2),
        (int)(GetScreenHeight() / 2.5f),
        50,
        SKYBLUE
      );
    }
    else {
      DrawText(
        "Player Vs. CPU",
        (GetScreenWidth() / 2) - (MeasureText("Player Vs. CPU", 50) / 2),
        (int)(GetScreenHeight() / 2.5f),
        50,
        RAYWHITE
      );
    }

    if (currentGameMode == 1) {
      DrawText(
        "* Player Vs. Player",
        (GetScreenWidth() / 2) - (MeasureText("* Player Vs. Player", 50) / 2),
        GetScreenHeight() / 2,
        50,
        SKYBLUE
      );
    }
    else {
      DrawText(
        "Player Vs. Player",
        (GetScreenWidth() / 2) - (MeasureText("Player Vs. Player", 50) / 2),
        GetScreenHeight() / 2,
        50,
        RAYWHITE
      );
    }

    DrawText(
      "Hit ENTER to start playing",
      (GetScreenWidth() / 2) - (MeasureText("Hit ENTER to start playing", 40) / 2),
      (int)(GetScreenHeight() / 1.2f),
      40,
      GRAY
    );
  } break;
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
    case PLAYER_VERSUS_PLAYER: {
      DrawLine(
        GetScreenWidth() / 2,
        0,
        GetScreenWidth() / 2,
        GetScreenHeight(),
        RAYWHITE
      );

      player.draw();
      player2.draw();
      ball.draw();

      DrawText(TextFormat("%i", player_score), GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
      DrawText(TextFormat("%i", player2_score), 3 * GetScreenWidth() / 4 - 20, 20, 80, RAYWHITE);
    } break;
    default: break;
    }
  } break;
  default: break;
  }
}

void init() {
  InitWindow(screen::WIDTH, screen::HEIGHT, "Ping Pong");
  InitAudioDevice();
  SetExitKey(KEY_NULL); // Disable ESC exiting
  SetTargetFPS(60);

  Image icon = LoadImage("resources/icon.png");
  SetWindowIcon(icon);
  UnloadImage(icon);

  BallPaddleCollision = LoadSound("resources/sounds/ball-paddle.ogg");
  BallTableCollision = LoadSound("resources/sounds/ball-table.ogg");

  currentScreen = LOGO;
  currentGameMode = PLAYER_VERSUS_CPU;

  player = Paddle{};
  player.x = 10;
  player.y = (GetScreenHeight() / 2.0f) - (player.height / 2.0f);

  player2 = Paddle{};
  player2.x = GetScreenWidth() - (player2.width + 10.0f);
  player2.y = (GetScreenHeight() / 2.0f) - (player2.height / 2.0f);

  computer = CpuPaddle{};
  computer.x = GetScreenWidth() - (computer.width + 10.0f);
  computer.y = (GetScreenHeight() / 2.0f) - (computer.height / 2.0f);

  ball = Ball{};

  player_score = 0;
  player2_score = 0;
  computer_score = 0;
}

void quit() {
  UnloadSound(BallPaddleCollision);
  UnloadSound(BallTableCollision);

  CloseAudioDevice();
  CloseWindow();
}

int main() {
  init();

  while (!WindowShouldClose()) {
    update();

    BeginDrawing();

    ClearBackground(Color{ 42, 42, 42, 255 });

    drawScene();

    EndDrawing();
  }

  quit();

  return 0;
}
