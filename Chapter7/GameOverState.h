#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include <string>
#include "MenuState.h"

class GameOverState : public MenuState {
  public:
    virtual void update(void);
    virtual void render(void);
    virtual bool onEnter(void);
    virtual std::string getStateId(void) const { return sStateId; }

  private:
    static const std::string sStateId;

    static GameState *sTransitionState;
    static void sGameOverToMain();
    static void sRestartPlay();
};

#endif // GAME_OVER_STATE_H

