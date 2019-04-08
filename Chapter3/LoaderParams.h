#ifndef LOADER_PARAMS_H
#define LOADER_PARAMS_H

#include <SDL2/SDL.h>
#include <string>

class LoaderParams {
  public:
    LoaderParams(
      std::string pTextureId,
      int pX,
      int pY,
      int pWidth,
      int pHeight,
      double pScale = 1.0,
      double pRotation = 0.0,
      SDL_RendererFlip pFlip = SDL_FLIP_NONE,
      int pAnimationCounter = 0,
      int pAnimationFrame = 0,
      int pAnimationRow = 0
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

  protected:
    std::string mTextureId;
    int mX, mY, mWidth, mHeight;
    double mScale, mRotation;
    SDL_RendererFlip mFlip;
    int mAnimationCounter, mAnimationFrame, mAnimationRow;
};

#endif // LOADER_PARAMS_H

