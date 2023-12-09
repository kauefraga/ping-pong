#include "Game.h"


Game::Game() {
  InitializeWindow();
  LoadResources();
}

void Game::InitializeWindow() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ping Pong");
  InitAudioDevice();
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  Image icon = LoadImage("resources/icon.png");
  SetWindowIcon(icon);
  UnloadImage(icon);

  currentScene = 0;
  currentGameMode = 0;

  soundTrack = LoadMusicStream("resources/sounds/jazz-sound-track.mp3");
  SetMusicVolume(soundTrack, 0.1f);
  PlayMusicStream(soundTrack);
}

void Game::LoadResources() {
  startScene.Load();
  gamemodeScene.Load();
  gameplayScene.Load();
}

void Game::UnloadAndClose() {
  startScene.Unload();
  gamemodeScene.Unload();
  gameplayScene.Unload();

  UnloadMusicStream(soundTrack);

  CloseAudioDevice();
  CloseWindow();
}

void Game::Update() {
  updateMusic(soundTrack, pauseMusic, timePlayed);

  if (currentScene == 0) startScene.Update(currentScene);

  if (currentScene == 1) gamemodeScene.Update(currentScene, currentGameMode);

  if (currentScene == 2) gameplayScene.Update(currentScene, currentGameMode);
}

void Game::Render() {
  BeginDrawing();
  ClearBackground(Color{ 42, 42, 42, 255 });

  if (currentScene == 0) startScene.Render();

  if (currentScene == 1) gamemodeScene.Render(currentGameMode);

  if (currentScene == 2) gameplayScene.Render();

  EndDrawing();
}

bool Game::IsRunning() {
  if (!WindowShouldClose()) {
    return true;
  }

  return false;
}
