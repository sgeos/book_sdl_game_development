#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "BaseCreator.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"

class Player : public PlatformerObject {
  public:
    Player(void);
    virtual ~Player(void) { }
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "Player"; }

  private:
    bool mInvulnerable;
    int mInvulnerableTime;
    int mInvulnerableCounter;
    bool mJumpInput;

    void ressurect(void);
    void handleInput(void);
    void handleAnimation(void);
    void handleMovement(Vector2D pVelocity);
};

class PlayerCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new Player();
  }
};

#endif // PLAYER_H

