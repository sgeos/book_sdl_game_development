#include <cmath>
#include <SDL2/SDL.h>

#include "Game.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"

SdlGameObject::SdlGameObject(const LoaderParams *pParams) {
  mTextureId = pParams->getTextureId();
  mX = pParams->getX();
  mY = pParams->getY();
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
    Game::Instance()->getRenderer(),
    mTextureId,
    mX, mY, mWidth, mHeight,
    mAnimationRow, mAnimationFrame,
    mScale, mRotation, mFlip
  );
}

void SdlGameObject::update(void) {
  mAnimationCounter++;
}

void SdlGameObject::cleanup(void) { }

