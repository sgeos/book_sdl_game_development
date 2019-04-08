#include <cstdlib>
#include "Game.h"

int main(int argc, char** argv) {
  Game *game = Game::Instance();
  while (false == game->isDone()) {
    game->tick();
  }
  bool exitStatus = game->isError() ? EXIT_FAILURE : EXIT_SUCCESS;
  delete game;
  return exitStatus;
}

