#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL2/SDL.h>
#include <string>

class GameObject {
  public:
    virtual void load(int pX, int pY, int pWidth, int pHeight, std::string pTextureId);
    virtual void draw(SDL_Renderer *pRenderer);
    virtual void update();
    virtual void cleanup();

  protected:
    std::string mTextureId;
    int mAnimationCounter, mAnimationFrame, mAnimationRow;
    int mX, mY, mWidth, mHeight;
    double mScale, mRotation;
    SDL_RendererFlip mFlip;
};

#endif // GAME_OBJECT_H

