#include <iostream>
#include <string>
#include "Constants.h"
#include "DemoBackground.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "TextureManager.h"

const std::string MenuState::sStateId = "MENU";

GameState *MenuState::sTransitionState = nullptr;

void MenuState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  if (nullptr != sTransitionState) {
    Game::Instance()->getStateMachine()->changeState(sTransitionState);
  }
}

void MenuState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool MenuState::onEnter(void) {
  sTransitionState = nullptr;
  const std::string resourcePath = Constants::ResourcePath("");
  bool success = TextureManager::Instance()->load("play_button", resourcePath + "play_button.png");
  success = success && TextureManager::Instance()->load("exit_button", resourcePath + "exit_button.png");
  success = success && TextureManager::Instance()->load("background", resourcePath + "background.png");
  if (success) {
    int tileWidth, tileHeight;
    TextureManager::Instance()->queryTexture("background", nullptr, nullptr, &tileWidth, &tileHeight);
    mGameObjectList.push_back(new DemoBackground(new LoaderParams("background", 0, 0, tileWidth, tileHeight)));
    int x, y, w, h;
    x = 100;
    y = 100;
    w = 400;
    h = 100;
    mGameObjectList.push_back(new MenuButton(new LoaderParams("play_button", x, y, w, h), sMenuToPlay));
    y = 300;
    mGameObjectList.push_back(new MenuButton(new LoaderParams("exit_button", x, y, w, h), sExitMenu));
    std::cout << "Entering MenuState \"" << sStateId << "\"." << std::endl;
  }
  return success;
}

bool MenuState::onExit(void) {
  while (false == mGameObjectList.empty()) {
    delete mGameObjectList.back();
    mGameObjectList.pop_back();
  }
  mGameObjectList.clear();
  TextureManager::Instance()->unload("play_button");
  TextureManager::Instance()->unload("exit_button");
  TextureManager::Instance()->unload("background");
  std::cout << "Exiting MenuState \"" << sStateId << "\"." << std::endl;
  return true;
}

void MenuState::sMenuToPlay(void) {
  sTransitionState = new PlayState();
}

void MenuState::sExitMenu(void) {
  Game::Instance()->getStateMachine()->popState();
  //Game::Instance()->quit();
}

