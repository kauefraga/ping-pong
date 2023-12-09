#pragma once

#include <raylib.h>


class GamemodeScene {
public:
  void Load();
  void Unload();
  void Update(int& currentScene, int& currentGameMode);
  void Render(int& currentGameMode);
};
