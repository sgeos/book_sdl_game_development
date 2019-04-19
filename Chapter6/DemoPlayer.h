#ifndef DEMO_PLAYER_H
#define DEMO_PLAYER_H

#include "SdlGameObject.h"
#include "LoaderParams.h"

class DemoPlayer : public SdlGameObject {
  public:
    DemoPlayer(const LoaderParams *pParams);
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

#endif // DEMO_PLAYER_H

