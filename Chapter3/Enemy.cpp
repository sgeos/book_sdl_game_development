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
  mX += (int)(5.0 * cos(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  mY += (int)(5.0 * sin(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
}

void Enemy::cleanup(void) { }

