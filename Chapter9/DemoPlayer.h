#ifndef DEMO_PLAYER_H
#define DEMO_PLAYER_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"

class DemoPlayer : public PlatformerObject {
  public:
    DemoPlayer(void);
    ~DemoPlayer(void);
    void load(const std::unique_ptr<LoaderParams> &pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    void handleInput(void);
    virtual void collision(void);
    virtual std::string type(void) { return "DemoPlayer"; }

  private:
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

