#ifndef GAME_STATE_MACHINE_H
#define GAME_STATE_MACHINE_H

#include <vector>
#include "GameState.h"

class GameStateMachine {
  public:
    void changeState(GameState *pState);
    void pushState(GameState *pState);
    void popState(void);

  private:
    std::vector<GameState *> mStateStack;
};

#endif // GAME_STATE_MACHINE_H

