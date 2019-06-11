#include <iostream>

#include <cmath>
#include <SDL2/SDL.h>

#include "Game.h"
#include "Player.h"
#include "Constants.h"
#include "InputHandler.h"
#include "PlatformerObject.h"
#include "TextureManager.h"

Player::Player(void) :
  PlatformerObject(),
  mTargetApproachSpeed(6),
  mInvulnerable(false),
  mInvulnerableTime(200),
  mInvulnerableCounter(0)
  { }

Player::~Player(void) { }

void Player::load(const std::unique_ptr<LoaderParams> &pParams) {
  PlatformerObject::load(pParams);
}

void Player::draw(void) {
  PlatformerObject::draw();
}

void Player::update(void) {
  if (Game::Instance()->getLevelComplete()) {
    mVelocity.setX(3);
    mVelocity.setY(0);
    if (Game::Instance()->getWidth() <= mPosition.getX()) {
      Game::Instance()->setCurrentLevel(Game::Instance()->getCurrentLevel() + 1);
    }
  } else if (true == mDying) {
    mDyingCounter++;
    if (mDyingTime < mDyingCounter) {
      ressurect();
    }
  } else {
    mVelocity.setX(0);
    mVelocity.setY(0);
    handleInput();
  }
  handleAnimation();
  PlatformerObject::update();
}

void Player::cleanup(void) { }

void Player::collision(void) {
  if (!mInvulnerable && !Game::Instance()->getLevelComplete()) {
    mTextureId = "large_explosion";
    mAnimationFrame = 0;
    mAnimationFrameCount = 9;
    mWidth = 60;
    mHeight = 60;
    mDying = true;
  }
}

void Player::ressurect(void) {
  Game::Instance()->setPlayerLives(Game::Instance()->getPlayerLives() - 1);
  mPosition.setX(10);
  mPosition.setY(200);
  mRotation = 0.0f;
  mDying = false;
  mDyingCounter = 0;
  mDead = false;
  mInvulnerable = true;
  mTextureId = "player";
  mAnimationFrame = 0;
  mAnimationFrameCount = 4;
  mWidth = 101;
  mHeight = 46;
}

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

void Player::handleAnimation(void) {
  if (mInvulnerable && mInvulnerableCounter < mInvulnerableTime) {
    mAlpha = 0.5;
    mInvulnerableCounter++;
  } else {
    mInvulnerable = false;
    mInvulnerableCounter = 0;
    mAlpha = 1.0;
  }
  if (false == mDead) {
    int dY = (int)mVelocity.getY();
    if (SDL_FLIP_NONE == mFlip) {
      dY *= -1;
    }
    if ((dY < 0 && -10 < mRotation) || (0 == dY && 0 < mRotation)) {
      mRotation--;
    } else if ((0 < dY && mRotation < 10) || (0 == dY && mRotation < 0)) {
      mRotation++;
    }
  }
}

