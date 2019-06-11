#ifndef BULLET_H
#define BULLET_H

#include "LoaderParams.h"
#include "PlatformerObject.h"
#include "Vector2D.h"

class PlayerBullet : public PlatformerObject {
  public:
    PlayerBullet(void) : PlatformerObject() { }
    virtual ~PlayerBullet(void) { }
    virtual void load(const std::unique_ptr<LoaderParams> &pParams) { PlatformerObject::load(std::move(pParams)); }
    virtual void draw(void) { PlatformerObject::draw(); }
    virtual void update(void) {
      mVelocity.setX(mHeading.getX());
      mVelocity.setY(mHeading.getY());
      PlatformerObject::update();
    }
    virtual void cleanup(void) { PlatformerObject::cleanup(); }
    virtual void collision(void) { mDead = true; }
    virtual std::string type(void) { return "PlayerBullet"; }
    void setHeading(Vector2D pHeading) { mHeading = pHeading; }

  private:
    Vector2D mHeading;
};

class EnemyBullet : public PlayerBullet {
  public:
    EnemyBullet(void) : PlayerBullet() { }
    virtual ~EnemyBullet(void) { }
    virtual std::string type(void) { return "EnemyBullet"; }
};

#endif // BULLET_H

