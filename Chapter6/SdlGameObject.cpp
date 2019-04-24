#include <cmath>
#include <SDL2/SDL.h>

#include "Game.h"
#include "GameObject.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"

SdlGameObject::SdlGameObject(void) :
  mTextureId(""),
  mPosition(0.0, 0.0),
  mVelocity(0.0, 0.0),
  mAcceleration(0.0, 0.0),
  mWidth(0.0),
  mHeight(0.0),
  mScale(1.0),
  mRotation(0.0),
  mFlip(SDL_FLIP_NONE),
  mAnimationCounter(0),
  mAnimationFrame(0),
  mAnimationRow(0)
{ }

void SdlGameObject::load(const LoaderParams *pParams)
{
  mPosition = Vector2D(pParams->getX(), pParams->getY());
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

