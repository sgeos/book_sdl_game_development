#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <string>
#include "GameState.h"

class PlayState : public GameState {
  public:
    virtual void update(void);
    virtual void render(void);
    virtual bool onEnter(void);
    virtual std::string getStateId(void) const { return sStateId; }

  private:
    static const std::string sStateId;

    bool checkCollision(SdlGameObject *pObjectA, SdlGameObject *pObjectB);
};

#endif // PLAY_STATE_H

