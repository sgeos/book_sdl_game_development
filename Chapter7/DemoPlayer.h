#ifndef DEMO_PLAYER_H
#define DEMO_PLAYER_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"

class DemoPlayer : public SdlGameObject {
  public:
    DemoPlayer(void);
    void load(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    void handleInput(void);

  private:
    int mAnimationFrames;
    int mBaseRotation;
    float mOrbitScale;
    int mJoypadId;
    Vector2D mTarget;
    int mTargetApproachSpeed;
};

class DemoPlayerCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new DemoPlayer();
  }
};

#endif // DEMO_PLAYER_H

