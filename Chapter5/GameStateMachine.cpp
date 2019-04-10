#include <vector>
#include "GameStateMachine.h"

void GameStateMachine::changeState(GameState *pState) {
  if (false == mStateStack.empty()) {
    if (mStateStack.back()->getStateId() == pState->getStateId()) {
      return;
    }
    if (true == mStateStack.back()->onExit()) {
      delete mStateStack.back();
      mStateStack.pop_back();
    }
  }
  mStateStack.push_back(pState);
  pState->onEnter();
}

void GameStateMachine::pushState(GameState *pState) {
  mStateStack.push_back(pState);
  pState->onEnter();
}

void GameStateMachine::popState(void) {
  if (false == mStateStack.empty()) {
    if (true == mStateStack.back()->onExit()) {
      delete mStateStack.back();
      mStateStack.pop_back();
    }
  }
}

