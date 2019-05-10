#include <cmath>
#include <SDL2/SDL.h>

#include "Constants.h"
#include "DemoBackground.h"
#include "Game.h"
#include "LoaderParams.h"
#include "TextureManager.h"

DemoBackground::DemoBackground(int pMaxIntensity) : mTextureId(""), mTileWidth(0), mTileHeight(0), mMaxIntensity(pMaxIntensity) {
  // set mAnimationCounter, mXOffset, mYOffset, mRed, mGreen, mBlue, mAlpha
  update();
}

void DemoBackground::load(const LoaderParams *pParams) {
  mTextureId = pParams->getTextureId();
  mTileWidth = pParams->getWidth();
  mTileHeight = pParams->getHeight();
  mMaxIntensity = pParams->getMaxIntensity();
}

void DemoBackground::draw(void) {
  SDL_SetRenderDrawColor(Game::Instance()->getRenderer(), mRed, mGreen, mBlue, mAlpha);
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
  mAnimationCounter = Game::Instance()->getFrame();
  int framesPerCycle = 2.5 * Constants::FramesPerSecond();
  int hue = mAnimationCounter / framesPerCycle % 6;
  int intensity = mMaxIntensity * abs(cos((float)mAnimationCounter / (2 * framesPerCycle) * M_PI));
  mAlpha = 255;
  switch (hue) {
    case 0:
      mRed =  mMaxIntensity;
      mGreen = 0;
      mBlue = intensity;
      break;
    case 1:
      mRed = mMaxIntensity;
      mGreen = intensity;
      mBlue = 0;
      break;
    case 2:
      mRed = intensity;
      mGreen = mMaxIntensity;
      mBlue = 0;
      break;
    case 3:
      mRed = 0;
      mGreen = mMaxIntensity;
      mBlue = intensity;
      break;
    case 4:
      mRed = 0;
      mGreen = intensity;
      mBlue = mMaxIntensity;
      break;
    case 5:
      mRed = intensity;
      mGreen = 0;
      mBlue = mMaxIntensity;
      break;
  }
  mXOffset = cos((float)mAnimationCounter / (Constants::FramesPerSecond() * 3)) * mTileWidth;
  mYOffset = mAnimationCounter / 2;
}

void DemoBackground::cleanup(void) { }

