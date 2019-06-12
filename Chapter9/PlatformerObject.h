#ifndef PLATFORMER_OBJECT_H
#define PLATFORMER_OBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class PlatformerObject : public GameObject {
  public:
    virtual ~PlatformerObject(void) { }
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void) { }
    virtual void collision(void) { }
    virtual std::string type(void) { return "PlatformerObject"; }

  protected:
    int mBulletFiringSpeed, mBulletCounter;
    int mMovementSpeed;
    int mDyingTime, mDyingCounter;
    bool mPlayedDeathSound;
    bool mMoveLeft,mMoveRight;
    bool mRunning, mFalling;
    bool mCanJump, mJumping;
    Vector2D mLastSafePosition;
    int mJumpHeight;
    PlatformerObject(void) :
      GameObject(),
      mBulletFiringSpeed(0),
      mBulletCounter(0),
      mMovementSpeed(0),
      mDyingTime(0),
      mDyingCounter(0),
      mPlayedDeathSound(false),
      mMoveLeft(false),
      mMoveRight(false),
      mRunning(false),
      mFalling(false),
      mCanJump(false),
      mJumping(false),
      mLastSafePosition(0.0f, 0.0f)
    { }
    void doDyingAnimation(void);
    bool checkCollideTile(Vector2D pNewPosition);
};

#endif // PLATFORMER_OBJECT_H

