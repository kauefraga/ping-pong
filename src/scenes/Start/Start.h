#pragma once

#include <raylib.h>


class StartScene {
public:
  void Load();
  void Unload();
  void Update(int& currentScene);
  void Render();
};
