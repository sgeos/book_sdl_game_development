#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "PlatformerObject.h"
#include "LoaderParams.h"

class Enemy : public PlatformerObject {
  public:
    virtual std::string type(void) { return "Enemy"; }

  protected:
    int mHealth;

    Enemy(void) : PlatformerObject(), mHealth(0) { }
    Enemy(int pHealth) : PlatformerObject(), mHealth(pHealth) { }
    virtual ~Enemy(void) { }
};

// class EnemyCreator : public BaseCreator {
//   GameObject *createGameObject(void) const {
//     return new Enemy();
//   }
// };

#endif // ENEMY_H

