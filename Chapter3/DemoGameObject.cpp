#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Constants.h"
#include "DemoGameObject.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

DemoGameObject::DemoGameObject(const LoaderParams *pParams) : SdlGameObject(pParams) {
  mCenterX = mX;
  mCenterY = mY;
  TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
  mAnimationFrames /= mWidth;
}

void DemoGameObject::draw(void) {
  SdlGameObject::draw();
}

void DemoGameObject::update(void) {
  SdlGameObject::update();
  int oldX = mX;
  int oldY = mY;
  mScale = 1.0 + 0.5 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  int centerX = mCenterX - mWidth * mScale / 2;
  int centerY = mCenterY - mHeight * mScale / 2;
  mX = centerX * (1.0 + 0.5 * cos((float)mAnimationCounter / (2 * Constants::FramesPerSecond())));
  mY = centerY * (1.0 + 0.5 * sin((float)mAnimationCounter / Constants::FramesPerSecond()));
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
  mRotation = mAnimationCounter;
  SDL_RendererFlip xFlip = mX == oldX ? (SDL_RendererFlip)(mFlip & SDL_FLIP_HORIZONTAL) : oldX < mX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  SDL_RendererFlip yFlip = mY == oldY ? (SDL_RendererFlip)(mFlip & SDL_FLIP_VERTICAL) :  mY < oldY ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
  mFlip = (SDL_RendererFlip)(xFlip | yFlip);
}

void DemoGameObject::cleanup(void) { }

