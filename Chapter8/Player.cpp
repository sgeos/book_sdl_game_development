#include <iostream>

#include <cmath>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Constants.h"
#include "InputHandler.h"
#include "ShooterObject.h"
#include "TextureManager.h"

Player::Player(void) : ShooterObject(), mTargetApproachSpeed(6) { }

Player::~Player(void) { }

void Player::load(const std::unique_ptr<LoaderParams> &pParams) {
  ShooterObject::load(pParams);
}

void Player::draw(void) {
  ShooterObject::draw();
}

void Player::update(void) {
  ShooterObject::update();
  handleInput();
}

void Player::cleanup(void) { }

void Player::collision(void) { }

void Player::handleInput(void) {
  Vector2D *target = InputHandler::Instance()->getMousePosition();
  mVelocity = *target - mPosition;
  mVelocity -= Vector2D(mWidth, mHeight) / 2;
  int dX = (int)mVelocity.getX();
  dX = (-mTargetApproachSpeed < dX && dX < mTargetApproachSpeed) ? 0 : dX;
  mVelocity.normalize();
  mVelocity *= 0 == dX ? 0.0 : mTargetApproachSpeed;
  mFlip = 0 == dX ? mFlip : dX < 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
}

