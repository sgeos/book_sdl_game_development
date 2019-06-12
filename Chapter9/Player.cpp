#include <iostream>

#include <cmath>
#include <SDL2/SDL.h>

#include "Camera.h"
#include "Game.h"
#include "Player.h"
#include "Constants.h"
#include "InputHandler.h"
#include "PlatformerObject.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "TileLayer.h"

Player::Player(void) :
  PlatformerObject(),
  mInvulnerable(false),
  mInvulnerableTime(200),
  mInvulnerableCounter(0),
  mJumpInput(false)
{
  mJumpHeight = 80;
}

void Player::load(const std::unique_ptr<LoaderParams> &pParams) {
  PlatformerObject::load(pParams);
  mBulletFiringSpeed = 13;
  mMovementSpeed = 3;
  mBulletCounter = mBulletFiringSpeed;
  mDyingTime = 100;
  Camera::Instance()->setTarget(&mPosition);
}

void Player::draw(void) {
  TextureManager::Instance()->drawFrame(
    mTextureId,
    (Uint32)mPosition.getX() - Camera::Instance()->getPosition().getX(),
    (Uint32)mPosition.getY() - Camera::Instance()->getPosition().getY(),
    mWidth, mHeight,
    mAnimationRow, mAnimationFrame,
    mScale, mRotation, mAlpha, mFlip
  );
}

void Player::update(void) {
  if (!mDying) {
    if (470 <= mPosition.getY() + mHeight) {
      collision();
    }
    handleInput();
    if (mMoveLeft) {
      if (mRunning) {
        mVelocity.setX(-5);
      } else {
        mVelocity.setX(-2);
      }
    } else if (mMoveRight) {
      if (mRunning) {
        mVelocity.setX(5);
      } else {
        mVelocity.setX(2);
      }
    } else {
      mVelocity.setX(0);
    }
    if (mPosition.getY() < mLastSafePosition.getY() - mJumpHeight) {
      mJumping = false;
    }
    if (!mJumping) {
      mVelocity.setY(5);
    } else {
      mVelocity.setY(-5);
    }
    handleMovement(mVelocity);
  } else {
    mVelocity.setX(0);
    mVelocity.setY(5);
    if (mDyingCounter < mDyingTime) {
      mDyingCounter++;
    } else {
      ressurect();
    }
  }
  handleAnimation();
}

void Player::cleanup(void) {
  PlatformerObject::cleanup();
}

void Player::collision(void) {
  if (!mInvulnerable && !mDying) {
    mAnimationRow = 4;
    mAnimationFrame = 0;
    mAnimationFrameCount = 9;
    mWidth = 50;
    mDying = true;
  }
}

void Player::ressurect(void) {
  Game::Instance()->setPlayerLives(Game::Instance()->getPlayerLives() - 1);
  mPosition = mLastSafePosition;
  mDying = false;
  mDyingCounter = 0;
  mInvulnerable = true;
  mWidth = 40;
  mAnimationRow = 0;
  mAnimationFrame = 0;
  mAnimationFrameCount = 1;
}

void Player::handleInput() {
  if (
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT) &&
    mPosition.getX() < ((*mCollisionLayerList->begin())->getMapWidth() * 32)
  ) {
    mMoveRight = true;
    mMoveLeft = false;
  } else if (
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) &&
    32 < mPosition.getX()
  ) {
    mMoveRight = false;
    mMoveLeft = true;
  } else {
    mMoveRight = false;
    mMoveLeft = false;
  }
  mRunning = (mMoveRight || mMoveLeft) && InputHandler::Instance()->isKeyDown(SDL_SCANCODE_A);
  if (
    InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) &&
    mCanJump &&
    !mJumpInput
  ) {
    SoundManager::Instance()->playSoundEffect("jump", 0);
    if (!mJumpInput) {
      mJumping = true;
      mCanJump = false;
      mLastSafePosition = mPosition;
      mJumpInput = true;
    }
  }
  if (
    !InputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE) &&
    mCanJump
  ) {
    mJumpInput = false;
  }
}

void Player::handleAnimation() {
  if (mInvulnerable && mInvulnerableCounter < mInvulnerableTime) {
    mAlpha = 0.5;
    mInvulnerableCounter++;
  } else {
    mInvulnerable = false;
    mInvulnerableCounter = 0;
    mAlpha = 1.0;
  }
  if (false == mDead && false == mDying) {
    int dY = (int)mVelocity.getY();
    if (dY < 0) {
      mAnimationRow = 2;
      mAnimationFrame = 1;
      mAnimationFrameCount = 2;
    } else if (0 < dY) {
      mAnimationRow = 3;
      mAnimationFrame = 0;
      mAnimationFrameCount = 1;
    } else {
      int dX = (int)mVelocity.getX();
      mFlip = 0 == dX ? mFlip : 0 < dX ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
      if (0 == dX) {
        mAnimationRow = 0;
        mAnimationFrameCount = 1;
      } else {
        mAnimationRow = 1;
        mAnimationFrameCount = 4;
      }
    }
    if (mRunning) {
      mAnimationSpeed = 10;
    } else {
      mAnimationSpeed = 8;
    }
  } else {
    mAnimationFrame = mDyingCounter / mAnimationFrameCount;
  }
}

void Player::handleMovement(Vector2D pVelocity) {
  Vector2D newPosition = mPosition;
  newPosition.setX(mPosition.getX() + pVelocity.getX());
  if (false == checkCollideTile(newPosition)) {
    mPosition.setX(newPosition.getX());
  } else {
    mVelocity.setX(0);
  }
  newPosition = mPosition;
  newPosition.setY(newPosition.getY() + pVelocity.getY());
  if (false == checkCollideTile(newPosition)) {
    mPosition.setY(newPosition.getY());
  } else {
    mVelocity.setY(0);
    mLastSafePosition = mPosition;
    if (0 < pVelocity.getX()) {
      mLastSafePosition.setX(mLastSafePosition.getX() - 32);
    } else if (pVelocity.getX() < 0) {
      mLastSafePosition.setX(mLastSafePosition.getX() + 32);
    }
    mCanJump = true;
    mJumping = false;
  }
}

