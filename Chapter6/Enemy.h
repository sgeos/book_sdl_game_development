#ifndef ENEMY_H
#define ENEMY_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"

class Enemy : public SdlGameObject {
  public:
    Enemy(void);
    void load(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);

  private:
    int mAnimationFrames;
    int mRadiusX, mRadiusY;
};

class EnemyCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new Enemy();
  }
};

#endif // ENEMY_H

