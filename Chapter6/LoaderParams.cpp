#include <SDL2/SDL.h>
#include <string>
#include "LoaderParams.h"

LoaderParams::LoaderParams(
  std::string pTextureId,
  int pX,
  int pY,
  int pWidth,
  int pHeight,
  double pScale,
  double pRotation,
  SDL_RendererFlip pFlip,
  int pAnimationCounter,
  int pAnimationFrame,
  int pAnimationRow
) :
  mTextureId(pTextureId),
  mX(pX),
  mY(pY),
  mWidth(pWidth),
  mHeight(pHeight),
  mScale(pScale),
  mRotation(pRotation),
  mFlip(pFlip),
  mAnimationCounter(pAnimationCounter),
  mAnimationFrame(pAnimationFrame),
  mAnimationRow(pAnimationRow)
{ }

std::string LoaderParams::getTextureId() const {
  return mTextureId;
}

int LoaderParams::getX(void) const {
  return mX;
}

int LoaderParams::getY(void) const {
  return mY;
}

int LoaderParams::getWidth(void) const {
  return mWidth;
}

int LoaderParams::getHeight(void) const {
  return mHeight;
}

double LoaderParams::getScale(void) const {
  return mScale;
}

double LoaderParams::getRotation(void) const {
  return mRotation;
}

SDL_RendererFlip LoaderParams::getFlip(void) const {
  return mFlip;
}

int LoaderParams::getAnimationCounter(void) const {
  return mAnimationCounter;
}

int LoaderParams::getAnimationFrame(void) const {
  return mAnimationFrame;
}

int LoaderParams::getAnimationRow(void) const {
  return mAnimationRow;
}

