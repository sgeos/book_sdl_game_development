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
#include "MenuState.h"
#include "PlayState.h"
#include "TextureManager.h"

const std::string GameOverState::sStateId = "GAMEOVER";

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
  const std::string resourcePath = Constants::ResourcePath("");
  bool success = TextureManager::Instance()->load("gameover_label", resourcePath + "gameover.png");
  success = success && TextureManager::Instance()->load("main_menu_button", resourcePath + "main_menu_button.png");
  success = success && TextureManager::Instance()->load("restart_button", resourcePath + "restart_button.png");
  success = success && TextureManager::Instance()->load("gameover_background", resourcePath + "background.png");
  if (success) {
    int tileWidth, tileHeight;
    TextureManager::Instance()->queryTexture("gameover_background", nullptr, nullptr, &tileWidth, &tileHeight);
    mGameObjectList.push_back(new DemoBackground(new LoaderParams("gameover_background", 0, 0, tileWidth, tileHeight), 96));
    int x, y, w, h;
    TextureManager::Instance()->queryTexture("gameover_label", nullptr, nullptr, &w, &h);
    w /= 2;
    x = (Constants::WindowWidth() - w) / 2;
    y = 1 * Constants::WindowHeight() / 4 - h / 2;
    mGameObjectList.push_back(new AnimatedGameObject(new LoaderParams("gameover_label", x, y, w, h), 2));
    TextureManager::Instance()->queryTexture("main_menu_button", nullptr, nullptr, &w, &h);
    w /= 3;
    x = (Constants::WindowWidth() - w) / 2;
    y = 2 * Constants::WindowHeight() / 4 - h / 2;
    mGameObjectList.push_back(new MenuButton(new LoaderParams("main_menu_button", x, y, w, h), sGameOverToMain));
    y = 3 * Constants::WindowHeight() / 4 - h / 2;
    mGameObjectList.push_back(new MenuButton(new LoaderParams("restart_button", x, y, w, h), sRestartPlay));
    std::cout << "Entering GameOverState \"" << sStateId << "\"." << std::endl;
  }
  return true;
}

bool GameOverState::onExit(void) {
  while (false == mGameObjectList.empty()) {
    delete mGameObjectList.back();
    mGameObjectList.pop_back();
  }
  TextureManager::Instance()->unload("game_over_label");
  TextureManager::Instance()->unload("main_menu_button");
  TextureManager::Instance()->unload("restart_button");
  TextureManager::Instance()->unload("gameover_background");
  std::cout << "Exiting GameOverState \"" << sStateId << "\"." << std::endl;
  return true;
}

void GameOverState::sGameOverToMain() {
  sTransitionState = new MenuState();
}

void GameOverState::sRestartPlay() {
  sTransitionState = new PlayState();
}

