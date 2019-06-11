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
    PlatformerObject(void) :
      GameObject(),
      mBulletFiringSpeed(0),
      mBulletCounter(0),
      mMovementSpeed(0),
      mDyingTime(0),
      mDyingCounter(0),
      mPlayedDeathSound(false)
    { }
    void doDyingAnimation(void);

    int mBulletFiringSpeed, mBulletCounter;
    int mMovementSpeed;
    int mDyingTime, mDyingCounter;
    bool mPlayedDeathSound;
};

#endif // PLATFORMER_OBJECT_H

