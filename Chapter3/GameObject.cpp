#include <SDL2/SDL.h>

#include "GameObject.h"
#include "TextureManager.h"

void GameObject::load(int pX, int pY, int pWidth, int pHeight, std::string pTextureId) {
  mX = pX;
  mY = pY;
  mWidth = pWidth;
  mHeight = pHeight;
  mTextureId = pTextureId;
  mAnimationCounter = 0;
  mAnimationRow = 0;
  mAnimationFrame = 0;
  mScale = 1.0;
  mRotation = 0.0;
  mFlip = SDL_FLIP_NONE;
}

void GameObject::draw(SDL_Renderer *pRenderer) {
  TextureManager::Instance()->drawFrame(
    mTextureId,
    mX, mY, mWidth, mHeight,
    mAnimationRow, mAnimationFrame,
    pRenderer,
    mScale, mRotation, mFlip
  );
}

void GameObject::update() {
  mAnimationCounter++;
}

void GameObject::cleanup() {}

