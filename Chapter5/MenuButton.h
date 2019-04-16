#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "LoaderParams.h"
#include "SdlGameObject.h"

class MenuButton : public SdlGameObject {
  public:
    MenuButton(const LoaderParams *pParams, void (*pCallback)(void));
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void);

  private:
    void (*mCallback)(void);
    bool mRunCallback;
    bool mWasClicked;
    bool mWasOutOfBounds;

    enum button_state {
      MOUSE_OUT = 0,
      MOUSE_OVER = 1,
      CLICKED = 2
    };
};

#endif // MENU_BUTTON_H

