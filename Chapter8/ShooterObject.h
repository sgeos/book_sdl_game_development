#ifndef SHOOTER_OBJECT_H
#define SHOOTER_OBJECT_H

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class ShooterObject : public GameObject {
  public:
    virtual ~ShooterObject(void) { }
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void) { }
    virtual void collision(void) { }
    virtual std::string type(void) { return "ShooterObject"; }

  protected:
    ShooterObject(void) :
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

#endif // SHOOTER_OBJECT_H

