#ifndef ANIMATED_GAME_OBJECT_H
#define ANIMATED_GAME_OBJECT_H

#include "SdlGameObject.h"
#include "LoaderParams.h"

class AnimatedGameObject : public SdlGameObject {
  public:
    AnimatedGameObject(const LoaderParams *pParams, int pAnimationSpeed);
    void draw(void);
    void update(void);
    void cleanup(void);

  private:
    int mAnimationSpeed;
    int mAnimationFrames;
};

#endif // ANIMATED_GAME_OBJECT_H

