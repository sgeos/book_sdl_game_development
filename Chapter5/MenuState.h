#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <string>
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
};

#endif // MENU_STATE_H

