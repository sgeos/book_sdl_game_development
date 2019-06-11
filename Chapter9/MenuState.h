#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <vector>
#include "GameObject.h"
#include "GameState.h"

class MenuState : public GameState {
  protected:
    std::vector<void (*)(void)> mCallbackList;
    void setCallbacks(void);
};

#endif // MENU_STATE_H

