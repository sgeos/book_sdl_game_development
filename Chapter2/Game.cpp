#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Constants.h"
#include "Game.h"
#include "Log.h"
#include "Utility.h"

namespace {
  void renderTexture(SDL_Texture *pTexture, SDL_Renderer *pRenderer, SDL_Rect pDestination, SDL_Rect *pClip = nullptr) {
    SDL_RenderCopy(pRenderer, pTexture, pClip, &pDestination);
  }

  void renderTexture(
    SDL_Texture *pTexture,
    SDL_Renderer *pRenderer,
    int pPositionX,
    int pPositionY,
    int pWidth,
    int pHeight,
    SDL_Rect *pClip = nullptr
  ) {
    SDL_Rect destination;
    destination.x = pPositionX;
    destination.y = pPositionY;
    destination.w = pWidth;
    destination.h = pHeight;
    renderTexture(pTexture, pRenderer, destination, pClip);
  }

//  void renderTexture(SDL_Texture *pTexture, SDL_Renderer *pRenderer, int pPositionX, int pPositionY, SDL_Rect *pClip = nullptr) {
//    SDL_Rect destination;
//    destination.x = pPositionX;
//    destination.y = pPositionY;
//    if (nullptr == pClip) {
//      SDL_QueryTexture(pTexture, nullptr, nullptr, &destination.w, &destination.h);
//    } else {
//      destination.w = pClip->w;
//      destination.h = pClip->h;
//    }
//    renderTexture(pTexture, pRenderer, destination, pClip);
//  }

  TTF_Font *openFont(const std::string &pFontFileName, int pFontSize) {
    TTF_Font *font = TTF_OpenFont(pFontFileName.c_str(), pFontSize);
    if (nullptr == font) {
      Log::SdlError(std::cout, "TTF_OpenFont");
      return nullptr;
    }
    return font;
  }

  SDL_Texture *renderText(
    const std::string &pMessage,
    TTF_Font *pFont,
    SDL_Color pColor,
    SDL_Renderer *pRenderer
  ) {
    SDL_Surface *surface = TTF_RenderText_Blended(pFont, pMessage.c_str(), pColor);
    if (nullptr == surface) {
      Log::SdlError(std::cout, "TTF_RenderText");
      return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(pRenderer, surface);
    if (nullptr == texture) {
      Log::SdlError(std::cout, "CreateTexture");
    }
    SDL_FreeSurface(surface);
    return texture;
  }
}

Game::Game(void) : mWindow(nullptr), mRenderer(nullptr), mTexture(nullptr), mBackground(nullptr) {
  reset();
  std::cout << Constants::ApplicationName() << " Game Start." << std::endl;
}

Game::~Game(void) {
  cleanup();
  std::cout << Constants::ApplicationName() << " Last Frame: " << mFrame << std::endl;
}

void Game::cleanup(void) {
  Utility::cleanup(mBackground, mTexture, mRenderer, mWindow);
  TTF_Quit();
  SDL_Quit();
}

void Game::reset(void) {
  cleanup();
  if (0 != SDL_Init(SDL_INIT_VIDEO)) {
    Log::SdlError(std::cout, "SDL_Init");
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
  const std::string filename = resourcePath + "animate.bmp";
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
  mSourceRectangle.w /= Constants::AnimationFrames();
  TTF_Font *font = openFont(resourcePath + "twinklebear_ascii.ttf", 32);
  SDL_Color background_color = {0x00, 0x00, 0x00, 0x33};
  mBackground = renderText("Background  ...  ", font, background_color, mRenderer);
  TTF_CloseFont(font);
  if (nullptr == mBackground) {
    Utility::cleanup(mTexture, mRenderer, mWindow);
    mDone = mError = true;
    return;
  }
  mFrame = 0;
  mDone = mError = false;
}

void Game::render(void) {
  SDL_SetRenderDrawColor(mRenderer, mRed, mGreen, mBlue, mAlpha);
  SDL_RenderClear(mRenderer);
  int tileWidth, tileHeight;
  SDL_QueryTexture(mBackground, nullptr, nullptr, &tileWidth, &tileHeight);
  int offsetX = cos((float)mFrame / (Constants::FramesPerSecond() * 3)) * tileHeight - tileHeight;
  int offsetY = (mFrame / 2) % tileWidth - tileWidth;
  for (int y = offsetY; y < Constants::WindowHeight(); y += tileHeight) {
    for (int x = offsetX; x < Constants::WindowWidth(); x += tileWidth) {
      renderTexture(mBackground, mRenderer, x, y, tileWidth, tileHeight);
    }
  }
  SDL_RenderCopyEx(mRenderer, mTexture, &mSourceRectangle, &mDestinationRectangle, mFrame, nullptr, SDL_FLIP_HORIZONTAL);
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
  int animationIndex = mFrame * Constants::AnimationFrames() / Constants::FramesPerSecond() % Constants::AnimationFrames();
  mSourceRectangle.x = mSourceRectangle.w * animationIndex;
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

