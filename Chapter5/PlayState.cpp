#include <iostream>
#include <string>
#include "Constants.h"
#include "DemoBackground.h"
#include "Enemy.h"
#include "Game.h"
#include "GameOverState.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "PauseState.h"
#include "Vector2D.h"

const std::string PlayState::sStateId = "PLAY";

void PlayState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  int joypadId = 0;
  if (checkCollision(dynamic_cast<SdlGameObject *>(mGameObjectList[1]), dynamic_cast<SdlGameObject *>(mGameObjectList[2]))) {
    Game::Instance()->getStateMachine()->changeState(new GameOverState());
  } else if (InputHandler::Instance()->isButtonDown(joypadId, 5) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    Game::Instance()->getStateMachine()->pushState(new PauseState());
  }
}

void PlayState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool PlayState::onEnter(void) {
  const std::string resourcePath = Constants::ResourcePath("");
  bool success = TextureManager::Instance()->load("player", resourcePath + "helicopter0.png");
  success = success && TextureManager::Instance()->load("enemy", resourcePath + "helicopter1.png");
  success = success && TextureManager::Instance()->load("play_background", resourcePath + "background.png");
  if (success) {
    int tileWidth, tileHeight;
    TextureManager::Instance()->queryTexture("play_background", nullptr, nullptr, &tileWidth, &tileHeight);
    mGameObjectList.push_back(new DemoBackground(new LoaderParams("play_background", 0, 0, tileWidth, tileHeight)));
    int x, y, w, h;
    TextureManager::Instance()->queryTexture("player", nullptr, nullptr, &w, &h);
    w /= 5;
    x = (Constants::WindowWidth() - w) / 2;
    y = (Constants::WindowHeight() - h) / 2 - 200;
    mGameObjectList.push_back(new Enemy(new LoaderParams("enemy", x, y, w, h)));
    y = (Constants::WindowHeight() - h) / 2;
    mGameObjectList.push_back(new Player(new LoaderParams("player", x, y, w, h)));
    std::cout << "Entering PlayState \"" << sStateId << "\"." << std::endl;
  }
  return true;
}

bool PlayState::onExit(void) {
  while (false == mGameObjectList.empty()) {
    delete mGameObjectList.back();
    mGameObjectList.pop_back();
  }
  TextureManager::Instance()->unload("player");
  TextureManager::Instance()->unload("enemy");
  TextureManager::Instance()->unload("play_background");
  std::cout << "Exiting PlayState \"" << sStateId << "\"." << std::endl;
  return true;
}

bool PlayState::checkCollision(SdlGameObject *pObjectA, SdlGameObject *pObjectB) {
  int leftA, rightA, topA, bottomA;
  int leftB, rightB, topB, bottomB;

  leftA = pObjectA->getPosition().getX();
  rightA = leftA + pObjectA->getWidth();
  topA = pObjectA->getPosition().getY();
  bottomA = topA + pObjectA->getHeight();

  leftB = pObjectB->getPosition().getX();
  rightB = leftB + pObjectB->getWidth();
  topB = pObjectB->getPosition().getY();
  bottomB = topB + pObjectB->getHeight();

  return topA < bottomB && topB < bottomA && leftA < rightB && leftB < rightA;
}

