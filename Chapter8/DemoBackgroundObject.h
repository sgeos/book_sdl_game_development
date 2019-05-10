#ifndef DEMO_BACKGROUND_OBJECT_H
#define DEMO_BACKGROUND_OBJECT_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "SdlGameObject.h"
#include "LoaderParams.h"

class DemoBackgroundObject : public SdlGameObject {
  public:
    DemoBackgroundObject(void);
    void load(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
};

class DemoBackgroundObjectCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new DemoBackgroundObject();
  }
};

#endif // DEMO_BACKGROUND_OBJECT_H

