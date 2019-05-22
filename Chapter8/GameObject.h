#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <memory>
#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject {
  public:
    virtual ~GameObject(void) {}
    virtual void load(const std::unique_ptr<LoaderParams> &pParams) = 0;
    virtual void draw(void) = 0;
    virtual void update(void) = 0;
    virtual void cleanup(void) = 0;
    virtual void collision(void) = 0;
    virtual std::string type(void) = 0;
    Vector2D& getPosition(void) { return mPosition; }
    Vector2D& getVelocity(void) { return mVelocity; }
    int getWidth(void) { return mWidth; }
    int getHeight(void) { return mHeight; }
    void scroll(float pScrollSpeed) {
      if (std::string("Player") != type()) {
        mPosition.setX(mPosition.getX() - pScrollSpeed);
      }
    }
    void setUpdating(bool pUpdating) { mUpdating = pUpdating; }
    bool updating(void) { return mUpdating; }
    bool dying(void) { return mDying; }
    bool dead(void) { return mDead; }
        
  protected:
    GameObject(void) :
      mTextureId(""),
      mPosition(0.0f, 0.0f), mVelocity(0.0f, 0.0f), mAcceleration(0.0f, 0.0f),
      mWidth(0), mHeight(0),
      mScale(1.0), mRotation(0.0), mAlpha(1.0),
      mFlip(SDL_FLIP_NONE),
      mAnimationRow(0), mAnimationFrame(0), mAnimationFrameCount(1), mAnimationCounter(0), mAnimationSpeed(0),
      mUpdating(false), mDying(false), mDead(false)
    { }

    std::string mTextureId;
    Vector2D mPosition, mVelocity, mAcceleration;
    int mWidth, mHeight;
    double mScale, mRotation, mAlpha;
    SDL_RendererFlip mFlip;
    int mAnimationRow, mAnimationFrame, mAnimationFrameCount, mAnimationCounter, mAnimationSpeed;
    bool mUpdating, mDying, mDead;
};

#endif // GAME_OBJECT_H

