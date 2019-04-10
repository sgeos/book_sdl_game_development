#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.h"
#include "DemoBackground.h"
#include "DemoGameObject.h"
#include "Enemy.h"
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "TextureManager.h"
#include "Utility.h"

Game *Game::sInstance = nullptr;

Game::Game(void) : mWindow(nullptr), mRenderer(nullptr) {
  reset();
  std::cout << Constants::ApplicationName() << " Game Start." << std::endl;
}

Game::~Game(void) {
  cleanup();
  std::cout << Constants::ApplicationName() << " Last Frame: " << mFrame << std::endl;
}

void Game::cleanup(void) {
  while (false == mGameObjectList.empty()) {
    delete mGameObjectList.back();
    mGameObjectList.pop_back();
  }
  Utility::cleanup(mRenderer, mWindow);
  InputHandler::Instance()->reset();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Game::reset(void) {
  cleanup();
  if (0 != SDL_Init(SDL_INIT_VIDEO)) {
    Log::SdlError(std::cout, "SDL_Init");
    mDone = mError = true;
    return;
  }
  if (IMG_INIT_PNG != (IMG_INIT_PNG & IMG_Init(IMG_INIT_PNG))) {
    Log::SdlError(std::cout, "IMG_Init");
    mDone = mError = true;
    return;
  }
  if (0 != TTF_Init()) {
    Log::SdlError(std::cout, "TTF_Init");
    mDone = mError = true;
    return;
  }
  mWindow = SDL_CreateWindow(
    Constants::WindowTitle(),
    Constants::WindowPositionX(),
    Constants::WindowPositionY(),
    Constants::WindowWidth(),
    Constants::WindowHeight(),
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );
  if (nullptr == mWindow) {
    Log::SdlError(std::cout, "SDL_CreateWindow");
    mDone = mError = true;
    return;
  }
  mRenderer = SDL_CreateRenderer(
    mWindow,
    Constants::DefaultRendererWindow(),
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (nullptr == mRenderer) {
    Log::SdlError(std::cout, "SDL_CreateRenderer");
    Utility::cleanup(mWindow);
    mDone = mError = true;
    return;
  }
  const std::string resourcePath = Constants::ResourcePath("");
  TextureManager::Instance()->load(mRenderer, "object", resourcePath + "animate.png");
  TextureManager::Instance()->load(mRenderer, "background", resourcePath + "background.png");

  int w = 128;
  int h = 82;
  for (int j = 0; j < 5; j++) {
    for (int i = 0; i < 5; i++) {
      int x = i * Constants::WindowWidth() / 4 - w/2;
      int y = j * Constants::WindowHeight() / 4 - h / 2;
      SDL_RendererFlip xFlip = (0 != (i % 2)) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
      SDL_RendererFlip yFlip = (0 != (j % 2)) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
      SDL_RendererFlip flip = (SDL_RendererFlip)(xFlip | yFlip);
      mGameObjectList.push_back(new Enemy(new LoaderParams("object", x, y, w, h, 1.0, 0.0, flip)));
    }
  }
  int tileWidth, tileHeight;
  TextureManager::Instance()->queryTexture("background", nullptr, nullptr, &tileWidth, &tileHeight);
  mGameObjectList.push_back(new DemoBackground(new LoaderParams("object", 0, 0, tileWidth, tileHeight)));
  mGameObjectList.push_back(new DemoBackground(new LoaderParams("background", 0, 0, tileWidth, tileHeight)));
  int x = Constants::WindowWidth() / 2 - w / 2;
  int y;
  for (int i = 0; i < 5; i++) {
    y = i * Constants::WindowHeight() / 4 - h / 2;
    mGameObjectList.push_back(new Player(new LoaderParams("object", x, y, w, h)));
  }
  y = Constants::WindowHeight() / 2 - h / 2;
  mGameObjectList.push_back(new DemoGameObject(new LoaderParams("object", x, y, w, h)));
  InputHandler::Instance()->initialiseJoysticks();
  mFrame = 0;
  mDone = mError = false;
}

void Game::render(void) {
  SDL_RenderClear(mRenderer);
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
  SDL_RenderPresent(mRenderer);
  if (0 == mFrame % Constants::FramesPerSecond()) {
    std::cout << Constants::ApplicationName() << " Frame: " << mFrame << std::endl;
  }
}

void Game::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  mFrame++;
}

void Game::handleEvents(void) {
  InputHandler::Instance()->update();
}

void Game::tick(void) {
  Uint32 frameStart = SDL_GetTicks();
  handleEvents();
  update();
  render();
  int frameWait = (int)(Constants::FrameWait() + frameStart - SDL_GetTicks());
  if (0 < frameWait) {
    SDL_Delay(frameWait);
  }
}

int Game::getFrame(void) {
  return mFrame;
}

SDL_Renderer *Game::getRenderer(void) {
  return mRenderer;
}

void Game::quit(void) {
  mDone = true;
}

bool Game::isDone(void) {
  return mDone;
}

bool Game::isError(void) {
  return mError;
}

