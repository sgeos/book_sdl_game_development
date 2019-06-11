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
  double pAlpha,
  bool pXFlip,
  bool pYFlip,
  int pAnimationRow,
  int pAnimationFrame,
  int pAnimationFrameCount,
  int pAnimationCounter,
  int pAnimationSpeed,
  int pMaxIntensity,
  int pCallbackId
) :
  mTextureId(pTextureId),
  mX(pX),
  mY(pY),
  mWidth(pWidth),
  mHeight(pHeight),
  mScale(pScale),
  mRotation(pRotation),
  mAlpha(pAlpha),
  mFlip((SDL_RendererFlip)((pXFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | (pYFlip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE))),
  mAnimationRow(pAnimationRow),
  mAnimationFrame(pAnimationFrame),
  mAnimationFrameCount(pAnimationFrameCount),
  mAnimationCounter(pAnimationCounter),
  mAnimationSpeed(pAnimationSpeed),
  mMaxIntensity(pMaxIntensity),
  mCallbackId(pCallbackId)
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

double LoaderParams::getAlpha(void) const {
  return mAlpha;
}

SDL_RendererFlip LoaderParams::getFlip(void) const {
  return mFlip;
}

int LoaderParams::getAnimationRow(void) const {
  return mAnimationRow;
}

int LoaderParams::getAnimationFrame(void) const {
  return mAnimationFrame;
}

int LoaderParams::getAnimationFrameCount(void) const {
  return mAnimationFrameCount;
}

int LoaderParams::getAnimationCounter(void) const {
  return mAnimationCounter;
}

int LoaderParams::getAnimationSpeed(void) const {
  return mAnimationSpeed;
}

int LoaderParams::getMaxIntensity(void) const {
  return mMaxIntensity;
}

int LoaderParams::getCallbackId(void) const {
  return mCallbackId;
}

