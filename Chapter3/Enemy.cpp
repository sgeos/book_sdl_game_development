#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Enemy.h"
#include "Constants.h"
#include "SdlGameObject.h"

Enemy::Enemy(const LoaderParams *pParams) : SdlGameObject(pParams) { }

void Enemy::draw(void) {
  SdlGameObject::draw();
}

void Enemy::update(void) {
  SdlGameObject::update();
  mX += (int)(5.0 * cos(2.0 * M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  if (mX < 0) {
    mX = 0;
  }
  mY += (int)(5.0 * sin(2.0 * M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  if (mY < 0) {
    mY = 0;
  }
}

void Enemy::cleanup(void) { }

