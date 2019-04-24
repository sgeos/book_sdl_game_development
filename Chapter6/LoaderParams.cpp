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
  bool pXFlip,
  bool pYFlip,
  int pAnimationCounter,
  int pAnimationFrame,
  int pAnimationRow,
  int pAnimationSpeed,
  int pAnimationFrames,
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
  mFlip((SDL_RendererFlip)((pXFlip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | (pYFlip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE))),
  mAnimationCounter(pAnimationCounter),
  mAnimationFrame(pAnimationFrame),
  mAnimationRow(pAnimationRow),
  mAnimationSpeed(pAnimationSpeed),
  mAnimationFrames(pAnimationFrames),
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

int LoaderParams::getAnimationSpeed(void) const {
  return mAnimationSpeed;
}

int LoaderParams::getAnimationFrames(void) const {
  return mAnimationFrames;
}

int LoaderParams::getMaxIntensity(void) const {
  return mMaxIntensity;
}

int LoaderParams::getCallbackId(void) const {
  return mCallbackId;
}

