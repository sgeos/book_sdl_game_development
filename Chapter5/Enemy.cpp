#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Enemy.h"
#include "Constants.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

Enemy::Enemy(const LoaderParams *pParams) : SdlGameObject(pParams) {
  TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
  mAnimationFrames /= mWidth;
}

void Enemy::draw(void) {
  SdlGameObject::draw();
}

void Enemy::update(void) {
  SdlGameObject::update();
  mVelocity.setX(5.0 * cos(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  mVelocity.setY(5.0 * sin(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
}

void Enemy::cleanup(void) { }

