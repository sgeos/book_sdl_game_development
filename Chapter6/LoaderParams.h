#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <SDL2/SDL.h>
#include <string>

class LoaderParams {
  public:
    LoaderParams(
      std::string pTextureId,
      int pX = 0,
      int pY = 0,
      int pWidth = 0,
      int pHeight = 0,
      double pScale = 1.0,
      double pRotation = 0.0,
      bool pXFlip = false,
      bool pYFlip = false,
      int pAnimationCounter = 0,
      int pAnimationFrame = 0,
      int pAnimationRow = 0,
      int pAnimationSpeed = 1,
      int pAnimationFrames = 1,
      int pMaxIntensity = 255,
      int pCallbackId = 0
    );
    std::string getTextureId(void) const;
    int getX(void) const;
    int getY(void) const;
    int getWidth(void) const;
    int getHeight(void) const;
    double getScale(void) const;
    double getRotation(void) const;
    SDL_RendererFlip getFlip(void) const;
    int getAnimationCounter(void) const;
    int getAnimationFrame(void) const;
    int getAnimationRow(void) const;
    int getAnimationSpeed(void) const;
    int getAnimationFrames(void) const;
    int getMaxIntensity(void) const;
    int getCallbackId(void) const;

  protected:
    std::string mTextureId;
    int mX, mY, mWidth, mHeight;
    double mScale, mRotation;
    SDL_RendererFlip mFlip;
    int mAnimationCounter, mAnimationFrame, mAnimationRow;
    int mAnimationSpeed, mAnimationFrames;
    int mMaxIntensity;
    int mCallbackId;
};

#endif // LOADER_PARAMS_H

