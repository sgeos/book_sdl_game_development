#include <cmath>
#include <SDL2/SDL.h>

#include "Constants.h"
#include "DemoBackground.h"
#include "Game.h"
#include "LoaderParams.h"
#include "TextureManager.h"

DemoBackground::DemoBackground(const LoaderParams *pParams) {
  mTextureId = pParams->getTextureId();
  mXOffset = pParams->getX();
  mYOffset = pParams->getY();
  mTileWidth = pParams->getWidth();
  mTileHeight = pParams->getHeight();
  mAnimationCounter = -1;
  // set mRed, mGreen, mBlue, mAlpha
  update();
}

void DemoBackground::draw(void) {
  SDL_SetRenderDrawColor(Game::Instance()->getRenderer(),mRed, mGreen, mBlue, mAlpha);
  for (int y = mYOffset % mTileHeight - mTileHeight; y < Constants::WindowHeight(); y += mTileHeight) {
    for (int x = mXOffset % mTileWidth - mTileWidth; x < Constants::WindowWidth(); x += mTileWidth) {
      int xIndex = (int)((x - mXOffset) / mTileWidth);
      int yIndex = (int)((y - mYOffset) / mTileHeight);
      SDL_RendererFlip xFlip = (0 != (xIndex % 2)) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
      SDL_RendererFlip yFlip = (0 != (yIndex % 2)) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
      SDL_RendererFlip flip = (SDL_RendererFlip)(xFlip | yFlip);
      TextureManager::Instance()->draw(mTextureId, x, y, mTileWidth, mTileHeight, 1.0, 0.0, flip);
    }
  }
}

void DemoBackground::update(void) {
  mAnimationCounter++;
  int framesPerCycle = 2.5 * Constants::FramesPerSecond();
  int hue = mAnimationCounter / framesPerCycle % 6;
  int intensity = 255 * abs(cos((float)mAnimationCounter / (2 * framesPerCycle) * M_PI));
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
  mXOffset = cos((float)mAnimationCounter / (Constants::FramesPerSecond() * 3)) * mTileWidth;
  mYOffset = mAnimationCounter / 2;
}

void DemoBackground::cleanup(void) { }

