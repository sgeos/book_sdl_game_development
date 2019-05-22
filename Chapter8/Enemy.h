#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "ShooterObject.h"
#include "LoaderParams.h"

class Enemy : public ShooterObject {
  public:
    Enemy(void);
    ~Enemy(void);
    void load(const std::unique_ptr<LoaderParams> &pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "Enemy"; }

  private:
    int mRadiusX, mRadiusY;
};

class EnemyCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new Enemy();
  }
};

#endif // ENEMY_H

