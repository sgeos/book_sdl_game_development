#ifndef ANIMATED_GAME_OBJECT_H
#define ANIMATED_GAME_OBJECT_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "SdlGameObject.h"

class AnimatedGameObject : public SdlGameObject {
  public:
    AnimatedGameObject(void);
    void load(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);

  private:
    int mAnimationSpeed;
    int mAnimationFrames;
};

class AnimatedGameObjectCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new AnimatedGameObject();
  }
};

#endif // ANIMATED_GAME_OBJECT_H

