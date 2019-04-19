#include <cmath>
#include <SDL2/SDL.h>

#include "Game.h"
#include "GameObject.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"

SdlGameObject::SdlGameObject(const LoaderParams *pParams) :
  GameObject(pParams),
  mPosition(pParams->getX(), pParams->getY()),
  mVelocity(0.0, 0.0),
  mAcceleration(0.0, 0.0)
{
  mTextureId = pParams->getTextureId();
  mWidth = pParams->getWidth();
  mHeight = pParams->getHeight();
  mScale = pParams->getScale();
  mRotation = pParams->getRotation();
  mFlip = pParams->getFlip();
  mAnimationCounter = pParams->getAnimationCounter();
  mAnimationFrame = pParams->getAnimationFrame();
  mAnimationRow = pParams->getAnimationRow();
}

void SdlGameObject::draw(void) {
  TextureManager::Instance()->drawFrame(
    mTextureId,
    (int)mPosition.getX(), (int)mPosition.getY(), mWidth, mHeight,
    mAnimationRow, mAnimationFrame,
    mScale, mRotation, mFlip
  );
}

void SdlGameObject::update(void) {
  mAnimationCounter++;
  mVelocity += mAcceleration;
  mPosition += mVelocity;
}

void SdlGameObject::cleanup(void) { }

Vector2D &SdlGameObject::getPosition(void) {
  return mPosition;
}

int SdlGameObject::getWidth(void) {
  return mWidth;
}

int SdlGameObject::getHeight(void) {
  return mHeight;
}

