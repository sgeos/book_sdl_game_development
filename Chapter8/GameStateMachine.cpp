#include <vector>
#include "GameStateMachine.h"

void GameStateMachine::popAndChangeState(GameState *pState) {
  for (int i = 0; i < 2; i++) {
    if (false == mStateStack.empty()) {
      if (mStateStack.back()->getStateId() == pState->getStateId()) {
        return;
      }
      if (true == mStateStack.back()->onExit()) {
        delete mStateStack.back();
        mStateStack.pop_back();
      }
    }
  }
  mStateStack.push_back(pState);
  pState->onEnter();
}

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
  mStateStack.back()->onEnter();
}

void GameStateMachine::popState(void) {
  if (false == mStateStack.empty()) {
    if (true == mStateStack.back()->onExit()) {
      delete mStateStack.back();
      mStateStack.pop_back();
    }
  }
}

bool GameStateMachine::empty(void) {
  return mStateStack.empty();
}

void GameStateMachine::update(void) {
  if (false == mStateStack.empty()) {
    mStateStack.back()->update();
  }
}

void GameStateMachine::render(void) {
  if (false == mStateStack.empty()) {
    mStateStack.back()->render();
  }
}

