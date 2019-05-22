#ifndef DEMO_GAME_OBJECT_H
#define DEMO_GAME_OBJECT_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "ShooterObject.h"
#include "LoaderParams.h"

class DemoGameObject : public ShooterObject {
  public:
    DemoGameObject(void);
    ~DemoGameObject(void);
    void load(const std::unique_ptr<LoaderParams> &pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "DemoGameObject"; }
};

class DemoGameObjectCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new DemoGameObject();
  }
};

#endif // DEMO_GAME_OBJECT_H

