#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <string>
#include <vector>
#include "GameObject.h"
#include "MenuState.h"

class MainMenuState : public MenuState {
  public:
    virtual void update(void);
    virtual void render(void);
    virtual bool onEnter(void);
    virtual std::string getStateId(void) const { return sStateId; }

  private:
    static GameState *sTransitionState;
    static const std::string sStateId;

    static void sMenuToPlay(void);
    static void sExitMenu(void);
};

#endif // MAIN_MENU_STATE_H

