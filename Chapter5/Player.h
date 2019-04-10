#ifndef PLAYER_H
#define PLAYER_H

#include "SdlGameObject.h"
#include "LoaderParams.h"

class Player : public SdlGameObject {
  public:
    Player(const LoaderParams *pParams);
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

#endif // PLAYER_H

