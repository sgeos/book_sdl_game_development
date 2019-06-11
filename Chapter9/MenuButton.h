#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"

class MenuButton : public PlatformerObject {
  public:
    MenuButton(void);
    ~MenuButton(void);
    void load(const std::unique_ptr<LoaderParams> &pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "MenuButton"; }
    void setCallback(void (*pCallback)(void));
    int getCallbackId(void);

  private:
    void (*mCallback)(void);
    bool mCallbackId;
    bool mRunCallback;
    bool mWasClicked;
    bool mWasOutOfBounds;

    enum button_state {
      MOUSE_OUT = 0,
      MOUSE_OVER = 1,
      CLICKED = 2
    };
};

class MenuButtonCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new MenuButton();
  }
};

#endif // MENU_BUTTON_H

