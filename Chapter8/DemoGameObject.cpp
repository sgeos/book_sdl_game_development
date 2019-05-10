#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Constants.h"
#include "DemoGameObject.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

DemoGameObject::DemoGameObject(void) { }

void DemoGameObject::load(const LoaderParams *pParams) {
  SdlGameObject::load(pParams);
  if (0 == mAnimationFrames) {
    TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
    mAnimationFrames /= mWidth;
  }
}

void DemoGameObject::draw(void) {
  SdlGameObject::draw();
}

void DemoGameObject::update(void) {
  SdlGameObject::update();
  mScale = 1.0 - 0.5 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dX = 2.0 * cos((float)mAnimationCounter / (2.0 * Constants::FramesPerSecond()));
  float dY = 2.0 * cos((float)mAnimationCounter / (1.0 * Constants::FramesPerSecond()));
  mVelocity.setX(dX);
  mVelocity.setY(dY);
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
  mRotation = 90 * cos((float)mAnimationCounter / (1.0 * Constants::FramesPerSecond()));;
  SDL_RendererFlip xFlip = 0.0 == dX ? (SDL_RendererFlip)(mFlip & SDL_FLIP_HORIZONTAL) : dX < 0.0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  SDL_RendererFlip yFlip = 0.0 == dY ? (SDL_RendererFlip)(mFlip & SDL_FLIP_VERTICAL) :  dY < 0.0 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
  mFlip = (SDL_RendererFlip)(xFlip | yFlip);
}

void DemoGameObject::cleanup(void) { }

