#include <cmath>
#include <SDL2/SDL.h>

#include "Game.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"
#include "TextureManager.h"
#include "TileLayer.h"

void PlatformerObject::load(const std::unique_ptr<LoaderParams> &pParams) {
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

void PlatformerObject::draw(void) {
  TextureManager::Instance()->drawFrame(
    mTextureId,
    (int)mPosition.getX(), (int)mPosition.getY(), mWidth, mHeight,
    mAnimationRow, mAnimationFrame,
    mScale, mRotation, mAlpha, mFlip
  );
}

void PlatformerObject::update(void) {
  mVelocity += mAcceleration;
  mPosition += mVelocity;
  mAnimationCounter++;
  mAnimationFrame = (mAnimationCounter * mAnimationSpeed / 1000) % mAnimationFrameCount;
}

void PlatformerObject::doDyingAnimation(void) {
  mAnimationFrame = (mAnimationCounter * mAnimationSpeed / 1000) % mAnimationFrameCount;
  
  if (mDyingTime <= mDyingCounter) {
    mDead = true;
  }
  mDyingCounter++;
}

bool PlatformerObject::checkCollideTile(Vector2D pNewPosition) {
  if (Game::Instance()->getHeight() <= pNewPosition.getY() + mHeight) {
    return false;
  } else {
    for (
      std::vector<TileLayer *>::iterator iterator = mCollisionLayerList->begin();
      iterator != mCollisionLayerList->end();
      ++iterator
    ) {
      TileLayer *tileLayer = (*iterator);
      std::vector<std::vector<int>> tileList = tileLayer->getTileIdList();
      Vector2D layerPosition = tileLayer->getPosition();
      int x = layerPosition.getX() / tileLayer->getTileSize();
      int y = layerPosition.getY() / tileLayer->getTileSize();
      Vector2D startPosition = pNewPosition;
      startPosition.setX(startPosition.getX() + 15);
      startPosition.setY(startPosition.getY() + 20);
      Vector2D endPosition(pNewPosition.getX() + (mWidth - 15), pNewPosition.getY() + (mHeight - 4));
      for (int i = startPosition.getX(); i < endPosition.getX(); i++) {
        for (int j = startPosition.getY(); j < endPosition.getY(); j++) {
          int tileColumn = i / tileLayer->getTileSize();
          int tileRow = j / tileLayer->getTileSize();
          int tileId = tileList[tileRow + y][tileColumn + x];
          if (0 != tileId) {
            return true;
          }
        }
      }
    }
    return false;
  }
}

