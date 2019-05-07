#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Enemy.h"
#include "Constants.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

Enemy::Enemy(void) : mAnimationFrames(1), mRadiusX(250.0), mRadiusY(200.0) { }

void Enemy::load(const LoaderParams *pParams) {
  SdlGameObject::load(pParams);
  if (0 == mAnimationFrames) {
    TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
    mAnimationFrames /= mWidth;
  }
}

void Enemy::draw(void) {
  SdlGameObject::draw();
}

void Enemy::update(void) {
  SdlGameObject::update();
  mVelocity.setX(mRadiusX * 2.0 / 38.188 * cos(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  mVelocity.setY(mRadiusY * 2.0 / 38.188 * sin(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  int dX = (int)mVelocity.getX();
  mFlip = 0 == dX ? mFlip : dX < 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
}

void Enemy::cleanup(void) { }

