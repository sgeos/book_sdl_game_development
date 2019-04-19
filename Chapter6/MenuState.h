#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <string>
#include <vector>
#include "GameObject.h"
#include "GameState.h"

class MenuState : public GameState {
  public:
    virtual void update(void);
    virtual void render(void);
    virtual bool onEnter(void);
    virtual bool onExit(void);
    virtual std::string getStateId(void) const { return sStateId; }

  private:
    static const std::string sStateId;
    std::vector<GameObject *> mGameObjectList;

    static GameState *sTransitionState;
    static void sMenuToPlay(void);
    static void sExitMenu(void);
};

#endif // MENU_STATE_H

