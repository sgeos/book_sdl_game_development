#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Enemy.h"
#include "Constants.h"
#include "ShooterObject.h"
#include "TextureManager.h"

Enemy::Enemy(void) : ShooterObject(), mRadiusX(250.0), mRadiusY(200.0) { }

Enemy::~Enemy(void) { }

void Enemy::load(const std::unique_ptr<LoaderParams> &pParams) {
  ShooterObject::load(pParams);
}

void Enemy::draw(void) {
  ShooterObject::draw();
}

void Enemy::update(void) {
  ShooterObject::update();
  mVelocity.setX(mRadiusX * 2.0 / 38.188 * cos(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  mVelocity.setY(mRadiusY * 2.0 / 38.188 * sin(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  int dX = (int)mVelocity.getX();
  mFlip = 0 == dX ? mFlip : dX < 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

void Enemy::cleanup(void) { }

void Enemy::collision(void) { }

