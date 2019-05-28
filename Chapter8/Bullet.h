#ifndef BULLET_H
#define BULLET_H

#include "ShooterObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

class PlayerBullet : public ShooterObject {
  public:
    PlayerBullet(void) : ShooterObject() { }
    virtual ~PlayerBullet(void) { }
    virtual void load(const std::unique_ptr<LoaderParams> &pParams) { ShooterObject::load(std::move(pParams)); }
    virtual void draw(void) { ShooterObject::draw(); }
    virtual void update(void) {
      mVelocity.setX(mHeading.getX());
      mVelocity.setY(mHeading.getY());
      ShooterObject::update();
    }
    virtual void cleanup(void) { ShooterObject::cleanup(); }
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

