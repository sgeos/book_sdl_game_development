#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <string>
#include "GameState.h"

class PlayState : public GameState {
  public:
    virtual void update(void);
    virtual void render(void);
    virtual bool onEnter(void);
    virtual bool onExit(void);
    virtual std::string getStateId(void) const { return sStateId; }

  private:
    static const std::string sStateId;
    std::vector<GameObject *> mGameObjectList;
};

#endif // PLAY_STATE_H

