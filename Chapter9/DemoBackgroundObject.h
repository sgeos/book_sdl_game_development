#ifndef DEMO_BACKGROUND_OBJECT_H
#define DEMO_BACKGROUND_OBJECT_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"

class DemoBackgroundObject : public PlatformerObject {
  public:
    DemoBackgroundObject(void);
    ~DemoBackgroundObject(void);
    void load(const std::unique_ptr<LoaderParams> &pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "DemoBackgroundObject"; }
};

class DemoBackgroundObjectCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new DemoBackgroundObject();
  }
};

#endif // DEMO_BACKGROUND_OBJECT_H

