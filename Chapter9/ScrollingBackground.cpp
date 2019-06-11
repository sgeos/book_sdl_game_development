#include "Game.h"
#include "PlatformerObject.h"
#include "ScrollingBackground.h"
#include "TextureManager.h"

ScrollingBackground::ScrollingBackground(void) :
  PlatformerObject(),
  mScrollSpeed(1),
  mCount(0),
  mMaxCount(10)
{ }

void ScrollingBackground::load(const std::unique_ptr<LoaderParams> &pParams) {
  PlatformerObject::load(pParams);
  mScrollSpeed = pParams->getAnimationSpeed();
  // mScrollSpeed = 1;
  reset();
}

void ScrollingBackground::draw(void) {
  TextureManager::Instance()->drawRaw(mTextureId, &mSourceRectangleA, &mDestinationRectangleA);
  TextureManager::Instance()->drawRaw(mTextureId, &mSourceRectangleB, &mDestinationRectangleB);
}

void ScrollingBackground::update(void) {
  if (mMaxCount <= mCount) {
    // make rectangle A smaller
    mSourceRectangleA.x += mScrollSpeed;
    mSourceRectangleA.w -= mScrollSpeed;
    // mDestinationRectangleA.x = mPosition.getX();
    mDestinationRectangleA.w -= mScrollSpeed;
    // make rectangle B bigger
    // mSourceRectangleB.x = 0;
    mSourceRectangleB.w += mScrollSpeed;
    mDestinationRectangleB.x -= mScrollSpeed;
    mDestinationRectangleB.w += mScrollSpeed;
    // reset and start again
    if (mWidth <= mDestinationRectangleB.w) {
      reset();
    }
    mCount = 0;
  }
  mCount++;
}

void ScrollingBackground::cleanup(void) {
  PlatformerObject::cleanup();
}

void ScrollingBackground::reset(void) {
  mSourceRectangleA.x = 0;
  mSourceRectangleA.y = 0;
  mSourceRectangleA.w = mWidth;
  mSourceRectangleA.h = mHeight;
  mDestinationRectangleA.x = mPosition.getX();
  mDestinationRectangleA.y = mPosition.getY();
  mDestinationRectangleA.w = mWidth;
  mDestinationRectangleA.h = mHeight;
  mSourceRectangleB.x = 0;
  mSourceRectangleB.y = 0;
  mSourceRectangleB.w = 0;
  mSourceRectangleB.h = mHeight;
  mDestinationRectangleB.x = mPosition.getX() + mWidth;
  mDestinationRectangleB.y = mPosition.getY();
  mDestinationRectangleB.w = 0;
  mDestinationRectangleB.h = mHeight;
}

