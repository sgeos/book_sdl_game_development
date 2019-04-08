#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.h"
#include "Enemy.h"
#include "Game.h"
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
  Utility::cleanup(mRenderer, mWindow);
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
  mTextureManager = TextureManager::Instance();
  const std::string resourcePath = Constants::ResourcePath("");
  mTextureManager->load(mRenderer, "object", resourcePath + "animate.png");
  mTextureManager->load(mRenderer, "background", resourcePath + "background.png");

  mGameObjectList.push_back(new Player(new LoaderParams("object", 0, 0, 128, 82)));
  for (int i = 0; i < 3; i++) {
    int position = (i + 1) * 100;
    mGameObjectList.push_back(new Enemy(new LoaderParams("object", position, position, 128, 82)));
  }
  mFrame = 0;
  mDone = mError = false;
}

void Game::render(void) {
  SDL_SetRenderDrawColor(mRenderer, mRed, mGreen, mBlue, mAlpha);
  SDL_RenderClear(mRenderer);
  int tileWidth, tileHeight;
  mTextureManager->queryTexture("background", nullptr, nullptr, &tileWidth, &tileHeight);
  int offsetX = cos((float)mFrame / (Constants::FramesPerSecond() * 3)) * tileHeight - tileHeight;
  int offsetY = (mFrame / 2) % tileWidth - tileWidth;
  for (int y = offsetY; y < Constants::WindowHeight(); y += tileHeight) {
    for (int x = offsetX; x < Constants::WindowWidth(); x += tileWidth) {
      SDL_RendererFlip flip = x / tileWidth % 2 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE | y / tileHeight % 2 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
      mTextureManager->draw(mRenderer, "background", x, y, tileWidth, tileHeight, 1.0, 0.0, flip);
    }
  }
  int objectWidth, objectHeight;
  mTextureManager->queryTexture("object", nullptr, nullptr, &objectWidth, &objectHeight);
  objectWidth /= Constants::AnimationFrames();
  int centerX = (Constants::WindowWidth() - objectWidth * mObjectScale) / 2;
  int centerY = (Constants::WindowHeight() - objectHeight * mObjectScale) / 2;
  mTextureManager->drawFrame(mRenderer, "object", centerX, centerY, objectWidth, objectHeight, 0, mObjectAnimationFrame);
  mTextureManager->drawFrame(mRenderer, "object", mObjectX, mObjectY, objectWidth, objectHeight, 0, mObjectAnimationFrame, mObjectScale, mObjectRotation, SDL_FLIP_HORIZONTAL);
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
  SDL_RenderPresent(mRenderer);
  if (0 == mFrame % Constants::FramesPerSecond()) {
    std::cout << Constants::ApplicationName() << " Frame: " << mFrame << std::endl;
  }
}

void Game::update(void) {
  int framesPerCycle = 2.5 * Constants::FramesPerSecond();
  int hue = mFrame / framesPerCycle % 6;
  int intensity = 255 * abs(cos((float)mFrame / (2 * framesPerCycle) * M_PI));
  mAlpha = 255;
  switch (hue) {
    case 0:
      mRed =  255;
      mGreen = 0;
      mBlue = intensity;
      break;
    case 1:
      mRed = 255;
      mGreen = intensity;
      mBlue = 0;
      break;
    case 2:
      mRed = intensity;
      mGreen = 255;
      mBlue = 0;
      break;
    case 3:
      mRed = 0;
      mGreen = 255;
      mBlue = intensity;
      break;
    case 4:
      mRed = 0;
      mGreen = intensity;
      mBlue = 255;
      break;
    case 5:
      mRed = intensity;
      mGreen = 0;
      mBlue = 255;
      break;
  }
  int objectWidth, objectHeight;
  mTextureManager->queryTexture("object", nullptr, nullptr, &objectWidth, &objectHeight);
  objectWidth /= Constants::AnimationFrames();
  mObjectScale = 1.0 + 0.5 * cos((float)mFrame / (Constants::FramesPerSecond() / 2));
  int centerX = (Constants::WindowWidth() - objectWidth * mObjectScale) / 2;
  int centerY = (Constants::WindowHeight() - objectHeight * mObjectScale) / 2;
  mObjectX = centerX * (1.0 + 0.5 * cos((float)mFrame / (2 * Constants::FramesPerSecond())));
  mObjectY = centerY * (1.0 + 0.5 * sin((float)mFrame / Constants::FramesPerSecond()));
  mObjectAnimationFrame = mFrame * Constants::AnimationFrames() / Constants::FramesPerSecond() % Constants::AnimationFrames();
  mObjectRotation = mFrame;
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  mFrame++;
}

void Game::handleEvents(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
      case SDL_MOUSEBUTTONDOWN:
      case SDL_KEYDOWN:
        mDone = true;
        break;
      default:
        break;
    }
  }
}

void Game::tick(void) {
  handleEvents();
  update();
  render();
  SDL_Delay(Constants::FrameWait());
}

int Game::getFrame(void) {
  return mFrame;
}

SDL_Renderer *Game::getRenderer(void) {
  return mRenderer;
}

bool Game::isDone(void) {
  return mDone;
}

bool Game::isError(void) {
  return mError;
}

