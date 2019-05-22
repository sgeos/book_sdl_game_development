#ifndef ANIMATED_GAME_OBJECT_H
#define ANIMATED_GAME_OBJECT_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "ShooterObject.h"

class AnimatedGameObject : public ShooterObject {
  public:
    AnimatedGameObject(void);
    virtual ~AnimatedGameObject(void);
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "AnimatedGameObject"; }
};

class AnimatedGameObjectCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new AnimatedGameObject();
  }
};

#endif // ANIMATED_GAME_OBJECT_H

