#include <iostream>
#include <string>
#include "AnimatedGameObject.h"
#include "Constants.h"
#include "DemoBackground.h"
#include "Game.h"
#include "GameOverState.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string GameOverState::sStateId = "gameover";

GameState *GameOverState::sTransitionState = nullptr;

void GameOverState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  if (nullptr != sTransitionState) {
    Game::Instance()->getStateMachine()->changeState(sTransitionState);
  }
}

void GameOverState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool GameOverState::onEnter(void) {
  sTransitionState = nullptr;
  StateParser stateParser;
  stateParser.parseState("demo.xml", sStateId, &mGameObjectList, &mTextureIdList);
  mCallbackList.push_back(sGameOverToMain);
  mCallbackList.push_back(sRestartPlay);
  setCallbacks();
  std::cout << "Entering state \"" << sStateId << "\"." << std::endl;
  return true;
}

void GameOverState::sGameOverToMain() {
  sTransitionState = new MainMenuState();
}

void GameOverState::sRestartPlay() {
  sTransitionState = new PlayState();
}

