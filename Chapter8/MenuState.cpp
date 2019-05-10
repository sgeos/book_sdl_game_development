#include <vector>
#include "GameObject.h"
#include "MenuButton.h"
#include "MenuState.h"

void MenuState::setCallbacks(void) {
  int listSize = mGameObjectList.size();
  for (int i = 0; i < listSize; i++) {
    if (MenuButton *button = dynamic_cast<MenuButton *>(mGameObjectList[i])) {
      int index = button->getCallbackId();
      void (*callback)(void) = mCallbackList[index];
      button->setCallback(callback);
    }
  }
}

