#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "AnimatedGameObject.h"
#include "Constants.h"
#include "DemoBackground.h"
#include "DemoBackgroundObject.h"
#include "DemoGameObject.h"
#include "DemoPlayer.h"
#include "DemoState.h"
#include "Enemy.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "GameOverState.h"
#include "GameStateMachine.h"
#include "InputHandler.h"
#include "Log.h"
#include "MainMenuState.h"
#include "MenuButton.h"
#include "Player.h"
#include "Utility.h"

Game *Game::sInstance = nullptr;

Game::Game(void) : mWindow(nullptr), mRenderer(nullptr) {
  sInstance = this;
  GameObjectFactory::Instance()->registerType("AnimatedGameObject", new AnimatedGameObjectCreator());
  GameObjectFactory::Instance()->registerType("DemoBackground", new DemoBackgroundCreator());
  GameObjectFactory::Instance()->registerType("DemoBackgroundObject", new DemoBackgroundObjectCreator());
  GameObjectFactory::Instance()->registerType("DemoGameObject", new DemoGameObjectCreator());
  GameObjectFactory::Instance()->registerType("DemoPlayer", new DemoPlayerCreator());
  GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
  GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
  GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
  reset();
  std::cout << Constants::ApplicationName() << " Game Start." << std::endl;
}

Game::~Game(void) {
  cleanup();
  std::cout << Constants::ApplicationName() << " Last Frame: " << mFrame << std::endl;
}

void Game::cleanup(void) {
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
  InputHandler::Instance()->initialiseJoysticks();
  mGameStateMachine = new GameStateMachine();
  mGameStateMachine->changeState(new DemoState());
  mGameStateMachine->pushState(new MainMenuState());
  mFrame = 0;
  mPlayerLives = 3;
  mCurrentLevel = 1;
  mNextLevel = 2;
  mLevelComplete = false;
  mDone = mError = false;
}

void Game::render(void) {
  SDL_RenderClear(mRenderer);
  mGameStateMachine->render();
  SDL_RenderPresent(mRenderer);
  if (0 == mFrame % Constants::FramesPerSecond()) {
    std::cout << Constants::ApplicationName() << " Frame: " << mFrame << std::endl;
  }
}

void Game::update(void) {
  if (false == mGameStateMachine->empty()) {
    mGameStateMachine->update();
    mFrame++;
  } else {
    mDone = true;
  }
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

GameStateMachine *Game::getStateMachine(void) {
  return mGameStateMachine;
}

SDL_Renderer *Game::getRenderer(void) {
  return mRenderer;
}

int Game::getWidth(void) {
  return Constants::WindowWidth();
}

int Game::getHeight(void) {
  return Constants::WindowHeight();
}

void Game::setCurrentLevel(int pCurrentLevel) {
  mCurrentLevel = pCurrentLevel;
  mGameStateMachine->setTransitionState(new GameOverState());
  mLevelComplete = false;
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

