#ifndef SDL_GAME_OBJECT_H
#define SDL_GAME_OBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class SdlGameObject : public GameObject {
  public:
    SdlGameObject(const LoaderParams *pParams);
    virtual void draw();
    virtual void update();
    virtual void cleanup();

  protected:
    std::string mTextureId;
    Vector2D mPosition;
    Vector2D mVelocity;
    Vector2D mAcceleration;
    int mWidth, mHeight;
    double mScale, mRotation;
    SDL_RendererFlip mFlip;
    int mAnimationCounter, mAnimationFrame, mAnimationRow;
};

#endif // SDL_GAME_OBJECT_H

