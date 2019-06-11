#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include "Vector2D.h"

enum MouseButton {
  LEFT = 0,
  MIDDLE = 1,
  RIGHT = 2
};

class InputHandler {
  public:
    static InputHandler *Instance(void) {
      if (nullptr == sInstance) {
        sInstance = new InputHandler();
      }
      return sInstance;
    }
    void reset(void);
    void update(void);
    void initialiseJoysticks(void);
    bool isInitialized(void) { return mInitialized; }
    int xValue(int pDeviceId, int pAxisId);
    int yValue(int pDeviceId, int pAxisId);
    bool isButtonDown(int pDeviceId, int pButtonId);
    Vector2D *getMousePosition(void);
    bool isMouseButtonDown(int pButtonId);
    bool isKeyDown(SDL_Scancode pScancode);

  private:
    InputHandler(void);
    ~InputHandler(void);
    void onJoystickAxisMotionEvent(int pDeviceId, int pAxisId, int pAxisValue);
    void onJoystickButtonEvent(int pDeviceId, int pButtonId, int pIsDown);
    void onMouseMotionEvent(int pX, int pY);
    void onMouseButtonEvent(int pSdlButtonId, bool pIsDown);
    void onKeyEvent(void);

    int mJoystickDeadZone = 1000;
    static InputHandler *sInstance;
    std::vector<SDL_Joystick *> mJoystickList;
    std::vector<std::pair<Vector2D *, Vector2D *>> mJoystickAxisList;
    std::vector<std::vector<bool>> mJoystickButtonList;
    Vector2D mMousePosition;
    std::vector<bool> mMouseButtonList;
    const Uint8 *mKeyState;
    bool mInitialized;
};

#endif // INPUT_HANDLER_H

