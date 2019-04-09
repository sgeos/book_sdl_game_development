#include <cmath>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Constants.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

Player::Player(const LoaderParams *pParams) : SdlGameObject(pParams) {
  TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
  mAnimationFrames /= mWidth;
}

void Player::draw(void) {
  SdlGameObject::draw();
}

void Player::update(void) {
  SdlGameObject::update();
  mScale = 1.0 + 0.5 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dX = 5.0 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dY = 2.0 * sin((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  mVelocity.setX(dX);
  mVelocity.setY(dY);
  mAnimationFrame = mAnimationCounter * Constants::AnimationFrames() / Constants::FramesPerSecond() % mAnimationFrames;
  mFlip = 0.0 == dX ? mFlip : dX < 0.0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void Player::cleanup(void) { }

