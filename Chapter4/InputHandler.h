#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include <vector>
#include "Vector2D.h"

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

  private:
    InputHandler(void);
    ~InputHandler(void) { reset(); }

    int mJoystickDeadZone = 1000;
    static InputHandler *sInstance;
    std::vector<SDL_Joystick *> mJoystickList;
    std::vector<std::pair<Vector2D *, Vector2D *>> mJoystickAxisList;
    bool mInitialized;
};

#endif // INPUT_HANDLER_H

