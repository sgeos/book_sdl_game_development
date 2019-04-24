#ifndef DEMO_GAME_OBJECT_H
#define DEMO_GAME_OBJECT_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"

class DemoGameObject : public SdlGameObject {
  public:
    DemoGameObject(void);
    void load(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);

  private:
    int mAnimationFrames;
};

class DemoGameObjectCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new DemoGameObject();
  }
};

#endif // DEMO_GAME_OBJECT_H

