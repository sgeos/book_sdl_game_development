#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include <vector>

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

  private:
    InputHandler(void);
    ~InputHandler(void) { reset(); }

    static InputHandler *sInstance;
    std::vector<SDL_Joystick *> mJoystickList;
    bool mInitialized;
};

#endif // INPUT_HANDLER_H

