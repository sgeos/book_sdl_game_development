#include <cstdlib>
#include <SDL2/SDL.h>

#include "Constants.h"
#include "Game.h"

int main(int argc, char** argv) {
  Game *game = new Game();
  while (false == game->isDone()) {
    game->tick();
  }
  bool exitStatus = game->isError() ? EXIT_FAILURE : EXIT_SUCCESS;
  delete game;
  return exitStatus;
}

