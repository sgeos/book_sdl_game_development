#include <iostream>

#include <cmath>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Constants.h"
#include "InputHandler.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

Player::Player(void) : mAnimationFrames(0), mTargetApproachSpeed(6) { }

void Player::load(const LoaderParams *pParams) {
  SdlGameObject::load(pParams);
  if (0 == mAnimationFrames) {
    TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
    mAnimationFrames /= mWidth;
  }
}

void Player::draw(void) {
  SdlGameObject::draw();
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

void Player::update(void) {
  SdlGameObject::update();
  handleInput();
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
}

void Player::cleanup(void) { }

