#include <cmath>
#include <SDL2/SDL.h>

#include "Game.h"
#include "GameObject.h"
#include "ShooterObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"

void ShooterObject::load(const std::unique_ptr<LoaderParams> &pParams) {
  mTextureId = pParams->getTextureId();
  mPosition = Vector2D(pParams->getX(), pParams->getY());
  mWidth = pParams->getWidth();
  mHeight = pParams->getHeight();
  mScale = pParams->getScale();
  mRotation = pParams->getRotation();
  mAlpha = pParams->getAlpha();
  mFlip = pParams->getFlip();
  mAnimationRow = pParams->getAnimationRow();
  mAnimationFrame = pParams->getAnimationFrame();
  mAnimationFrameCount = pParams->getAnimationFrameCount();
  mAnimationCounter = pParams->getAnimationCounter();
  mAnimationSpeed = pParams->getAnimationSpeed();
  if (0 == mAnimationFrameCount) {
    TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrameCount, nullptr);
    mAnimationFrameCount /= mWidth;
  }
}

void ShooterObject::draw(void) {
  TextureManager::Instance()->drawFrame(
    mTextureId,
    (int)mPosition.getX(), (int)mPosition.getY(), mWidth, mHeight,
    mAnimationRow, mAnimationFrame,
    mScale, mRotation, mAlpha, mFlip
  );
}

void ShooterObject::update(void) {
  mVelocity += mAcceleration;
  mPosition += mVelocity;
  mAnimationCounter++;
  mAnimationFrame = (mAnimationCounter * mAnimationSpeed / 1000) % mAnimationFrameCount;
}

void ShooterObject::doDyingAnimation(void) {
  mAnimationFrame = (mAnimationCounter * mAnimationSpeed / 1000) % mAnimationFrameCount;
  
  if (mDyingTime <= mDyingCounter) {
    mDead = true;
  }
  mDyingCounter++;
}

