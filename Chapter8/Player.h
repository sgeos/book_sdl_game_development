#ifndef PLAYER_H
#define PLAYER_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "ShooterObject.h"
#include "LoaderParams.h"

class Player : public ShooterObject {
  public:
    Player(void);
    virtual ~Player();
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "Player"; }
    void handleInput(void);

  protected:
    int mTargetApproachSpeed;
};

class PlayerCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new Player();
  }
};

#endif // PLAYER_H

