#include <iostream>
#include <string>
#include "Constants.h"
#include "DemoBackground.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string PauseState::sStateId = "pause";

GameState *PauseState::sTransitionState = nullptr;

void PauseState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  if (nullptr != sTransitionState) {
    Game::Instance()->getStateMachine()->popAndChangeState(sTransitionState);
  }
}

void PauseState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool PauseState::onEnter(void) {
  sTransitionState = nullptr;
  StateParser stateParser;
  stateParser.parseState("demo.xml", sStateId, &mGameObjectList, &mTextureIdList);
  mCallbackList.push_back(sPauseToMain);
  mCallbackList.push_back(sResumePlay);
  setCallbacks();
  std::cout << "Entering state \"" << sStateId << "\"." << std::endl;
  return true;
}

void PauseState::sPauseToMain() {
  sTransitionState = new MainMenuState();
}

void PauseState::sResumePlay() {
  Game::Instance()->getStateMachine()->popState();
}

