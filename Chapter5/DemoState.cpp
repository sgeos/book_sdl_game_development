#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Constants.h"
#include "DemoBackground.h"
#include "DemoGameObject.h"
#include "DemoPlayer.h"
#include "DemoState.h"
#include "DemoBackgroundObject.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "TextureManager.h"

const std::string DemoState::sStateId = "DEMO";

void DemoState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  int joypadId = 0;
  if (InputHandler::Instance()->isButtonDown(joypadId, 5) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    Game::Instance()->getStateMachine()->pushState(new PauseState());
  }
}

void DemoState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool DemoState::onEnter(void) {
  std::cout << "Entering DemoState \"" << sStateId << "\"." << std::endl;
  const std::string resourcePath = Constants::ResourcePath("");
  TextureManager::Instance()->load("object", resourcePath + "animate.png");
  TextureManager::Instance()->load("demo_background", resourcePath + "background.png");
  const int w = 128;
  const int h = 82;
  for (int j = -1; j < 5; j++) {
    for (int i = 0; i < 5; i++) {
      int x = i * Constants::WindowWidth() / 4 - w / 2;
      int y = j * Constants::WindowHeight() / 4 - h / 2;
      SDL_RendererFlip xFlip = (0 != (i % 2)) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
      SDL_RendererFlip yFlip = (0 != (j % 2)) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
      SDL_RendererFlip flip = (SDL_RendererFlip)(xFlip | yFlip);
      mGameObjectList.push_back(new DemoBackgroundObject(new LoaderParams("object", x, y, w, h, 1.0, 0.0, flip)));
    }
  }
  int tileWidth, tileHeight;
  TextureManager::Instance()->queryTexture("demo_background", nullptr, nullptr, &tileWidth, &tileHeight);
  mGameObjectList.push_back(new DemoBackground(new LoaderParams("object", 0, 0, tileWidth, tileHeight)));
  mGameObjectList.push_back(new DemoBackground(new LoaderParams("demo_background", 0, 0, tileWidth, tileHeight)));
  int x = Constants::WindowWidth() / 2 - w / 2;
  int y;
  for (int i = 0; i < 5; i++) {
    y = i * Constants::WindowHeight() / 4 - h / 2;
    mGameObjectList.push_back(new DemoPlayer(new LoaderParams("object", x, y, w, h)));
  }
  y = Constants::WindowHeight() / 2 - h / 2;
  mGameObjectList.push_back(new DemoGameObject(new LoaderParams("object", x, y, w, h)));
  return true;
}

bool DemoState::onExit(void) {
  while (false == mGameObjectList.empty()) {
    delete mGameObjectList.back();
    mGameObjectList.pop_back();
  }
  TextureManager::Instance()->unload("object");
  TextureManager::Instance()->unload("demo_background");
  std::cout << "Exiting DemoState \"" << sStateId << "\"." << std::endl;
  return true;
}

