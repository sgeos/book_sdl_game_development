#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <string>
#include "MenuState.h"

class PauseState : public MenuState {
  public:
    virtual void update(void);
    virtual void render(void);
    virtual bool onEnter(void);
    virtual std::string getStateId(void) const { return sStateId; }

  private:
    static const std::string sStateId;

    static GameState *sTransitionState;
    static void sPauseToMain();
    static void sResumePlay();
};

#endif // PAUSE_STATE_H

