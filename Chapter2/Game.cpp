#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

#include "Constants.h"
#include "Game.h"
#include "Log.h"
#include "Utility.h"

Game::Game(void) : mWindow(nullptr), mRenderer(nullptr), mTexture(nullptr) {
  reset();
  std::cout << Constants::ApplicationName() << " Game Start." << std::endl;
}

Game::~Game(void) {
  cleanup();
  std::cout << Constants::ApplicationName() << " Last Frame: " << mFrame << std::endl;
}

void Game::cleanup(void) {
  Utility::cleanup(mTexture, mRenderer, mWindow);
  SDL_Quit();
}

void Game::reset(void) {
  cleanup();
  if (0 != SDL_Init(SDL_INIT_VIDEO)) {
    Log::SdlError(std::cout, "SDL_Init");
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
  const std::string filename = resourcePath + "rider.bmp";
  SDL_Surface *surface = SDL_LoadBMP(filename.c_str());
  if (nullptr == surface) {
    Log::SdlError(std::cout, "LoadBMP");
    Utility::cleanup(mRenderer, mWindow);
    mDone = mError = true;
    return;
  }
  mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_FreeSurface(surface);
  if (nullptr == mTexture) {
    Log::SdlError(std::cout, "CreateTextureFromSurface");
    Utility::cleanup(mRenderer, mWindow);
    mDone = mError = true;
    return;
  }
  mSourceRectangle.x = 0;
  mSourceRectangle.y = 0;
  SDL_QueryTexture(mTexture, nullptr, nullptr, &mSourceRectangle.w, &mSourceRectangle.h);
  mFrame = 0;
  mDone = mError = false;
}

void Game::render(void) {
  SDL_SetRenderDrawColor(mRenderer, mRed, mGreen, mBlue, mAlpha);
  SDL_RenderClear(mRenderer);
  SDL_RenderCopy(mRenderer, mTexture, &mSourceRectangle, &mDestinationRectangle);
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
  int imageWidth = mSourceRectangle.w * (1.0 + 0.5 * cos((float)mFrame / (Constants::FramesPerSecond() / 2)));
  int imageHeight = mSourceRectangle.h * (1.0 + 0.5 * sin((float)mFrame / (Constants::FramesPerSecond() / 2)));
  int centerX = (Constants::WindowWidth() - imageWidth) / 2;
  int centerY = (Constants::WindowHeight() - imageHeight) / 2;
  mDestinationRectangle.x = centerX * (1.0 + 0.5 * cos((float)mFrame / (2 * Constants::FramesPerSecond())));
  mDestinationRectangle.y = centerY * (1.0 + 0.5 * sin((float)mFrame / Constants::FramesPerSecond()));
  mDestinationRectangle.w = imageWidth;
  mDestinationRectangle.h = imageHeight;
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

bool Game::isDone(void) {
  return mDone;
}

bool Game::isError(void) {
  return mError;
}

