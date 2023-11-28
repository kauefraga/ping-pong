#include "Game.h"


int main() {
  Game game = Game();

  while (game.IsRunning()) {
    game.Update();
    game.Render();
  }

  game.UnloadAndClose();

  return 0;
}
