#include <cmath>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Constants.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

Player::Player(const LoaderParams *pParams) : SdlGameObject(pParams) {
  mCenterX = mX;
  mCenterY = mY;
  TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
  mAnimationFrames /= mWidth;
}

void Player::draw(void) {
  SdlGameObject::draw();
}

void Player::update(void) {
  SdlGameObject::update();
  int oldX = mX;
  mScale = 1.0 + 0.5 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  mX = mCenterX - mWidth * mScale;
  mY = mCenterY - mHeight * mScale;
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
  mFlip = mX == oldX ? mFlip : mX < oldX ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void Player::cleanup(void) { }

