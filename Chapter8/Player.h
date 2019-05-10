#ifndef PLAYER_H
#define PLAYER_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"

class Player : public SdlGameObject {
  public:
    Player(void);
    void load(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    void handleInput(void);

  private:
    int mAnimationFrames;
    int mTargetApproachSpeed;
};

class PlayerCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new Player();
  }
};

#endif // PLAYER_H

