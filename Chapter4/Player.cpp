#include <cmath>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Constants.h"
#include "InputHandler.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

Player::Player(const LoaderParams *pParams) : SdlGameObject(pParams) {
  TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
  mAnimationFrames /= mWidth;
  mBaseRotation = 0;
}

void Player::draw(void) {
  SdlGameObject::draw();
}

void Player::handleInput(void) {
  InputHandler *inputHandler = InputHandler::Instance();
  if (inputHandler->isInitialized()) {
    float ddX = inputHandler->xValue(0, 0) + inputHandler->xValue(0, 1);
    float ddY = inputHandler->yValue(0, 0) + inputHandler->yValue(0, 1);
    mAcceleration.setX(ddX);
    mAcceleration.setY(ddY);
    if (0 != ddY && mBaseRotation < 90 && -90 < mBaseRotation) {
      mBaseRotation += ddY;
    } else if (0 == ddY && 0 < mBaseRotation) {
      mBaseRotation--;
    } else if (0 == ddY && mBaseRotation < 0) {
      mBaseRotation++;
    }
  }
}

void Player::update(void) {
  SdlGameObject::update();
  handleInput();
  mScale = 1.0 + 0.5 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dX = 2.5 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dY = 1.0 * sin((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  mVelocity.setX(dX);
  mVelocity.setY(dY);
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
  float ddX = mAcceleration.getX();
  ddX += 0.0 == ddX ? dX : 0.0;
  mFlip = 0.0 == ddX ? mFlip : ddX < 0.0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  mRotation = SDL_FLIP_HORIZONTAL != (mFlip & SDL_FLIP_HORIZONTAL) ? mBaseRotation : -mBaseRotation;
}

void Player::cleanup(void) { }

