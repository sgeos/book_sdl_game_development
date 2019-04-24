#include <iostream>
#include <string>
#include "Constants.h"
#include "DemoBackground.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string MainMenuState::sStateId = "menu";

GameState *MainMenuState::sTransitionState = nullptr;

void MainMenuState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  if (nullptr != sTransitionState) {
    Game::Instance()->getStateMachine()->changeState(sTransitionState);
  }
}

void MainMenuState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool MainMenuState::onEnter(void) {
  sTransitionState = nullptr;
  StateParser stateParser;
  stateParser.parseState("demo.xml", sStateId, &mGameObjectList, &mTextureIdList);
  mCallbackList.push_back(sMenuToPlay);
  mCallbackList.push_back(sExitMenu);
  setCallbacks();
  std::cout << "Entering state \"" << sStateId << "\"." << std::endl;
  return true;
}

void MainMenuState::sMenuToPlay(void) {
  sTransitionState = new PlayState();
}

void MainMenuState::sExitMenu(void) {
  Game::Instance()->getStateMachine()->popState();
  //Game::Instance()->quit();
}

