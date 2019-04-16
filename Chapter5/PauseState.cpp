#include <iostream>
#include <string>
#include "Constants.h"
#include "DemoBackground.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "TextureManager.h"

const std::string PauseState::sStateId = "PAUSE";

GameState *PauseState::sTransitionState = nullptr;

void PauseState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  if (nullptr != sTransitionState) {
    Game::Instance()->getStateMachine()->popState();
    Game::Instance()->getStateMachine()->changeState(sTransitionState);
  }
}

void PauseState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool PauseState::onEnter(void) {
  sTransitionState = nullptr;
  const std::string resourcePath = Constants::ResourcePath("");
  bool success = TextureManager::Instance()->load("resume_button", resourcePath + "resume_button.png");
  success = success && TextureManager::Instance()->load("main_menu_button", resourcePath + "main_menu_button.png");
  success = success && TextureManager::Instance()->load("pause_background", resourcePath + "background.png");
  if (success) {
    int tileWidth, tileHeight;
    TextureManager::Instance()->queryTexture("pause_background", nullptr, nullptr, &tileWidth, &tileHeight);
    mGameObjectList.push_back(new DemoBackground(new LoaderParams("pause_background", 0, 0, tileWidth, tileHeight)));
    int x, y, w, h;
    TextureManager::Instance()->queryTexture("main_menu_button", nullptr, nullptr, &w, &h);
    w /= 3;
    x = (Constants::WindowWidth() - w) / 2;
    y = 1 * Constants::WindowHeight() / 3 - h / 2;
    mGameObjectList.push_back(new MenuButton(new LoaderParams("main_menu_button", x, y, w, h), sPauseToMain));
    y = 2 * Constants::WindowHeight() / 3 - h / 2;
    mGameObjectList.push_back(new MenuButton(new LoaderParams("resume_button", x, y, w, h), sResumePlay));
    std::cout << "Entering PauseState \"" << sStateId << "\"." << std::endl;
  }
  return true;
}

bool PauseState::onExit(void) {
  while (false == mGameObjectList.empty()) {
    delete mGameObjectList.back();
    mGameObjectList.pop_back();
  }
  TextureManager::Instance()->unload("main_menu_btton");
  TextureManager::Instance()->unload("resume_button");
  TextureManager::Instance()->unload("pause_background");
  std::cout << "Exiting PauseState \"" << sStateId << "\"." << std::endl;
  return true;
}

void PauseState::sPauseToMain() {
  sTransitionState = new MenuState();
}

void PauseState::sResumePlay() {
  Game::Instance()->getStateMachine()->popState();
}

