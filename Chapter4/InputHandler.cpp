#include <SDL2/SDL.h>
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"

InputHandler *InputHandler::sInstance;

InputHandler::InputHandler(void) {
  initialiseJoysticks();
}

void InputHandler::reset(void) {
  while (false == mJoystickList.empty()) {
    SDL_JoystickClose(mJoystickList.back());
    mJoystickList.pop_back();
  }
  mInitialized = false;
}

void InputHandler::update(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
      case SDL_MOUSEBUTTONDOWN:
      case SDL_KEYDOWN:
        Game::Instance()->quit();
        break;
      default:
        break;
    }
  }
}

void InputHandler::initialiseJoysticks(void) {
  reset();
  if (0 == SDL_WasInit(SDL_INIT_JOYSTICK)) {
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  }
  int joystickCount = SDL_NumJoysticks();
  for (int i = 0; i < joystickCount; i++) {
    SDL_Joystick *joystick = SDL_JoystickOpen(i);
    if (joystick) {
      mJoystickList.push_back(joystick);
    } else {
      Log::SdlError(std::cout, "SDL_JoystickOpen");
    }
  }
  int initializedCount = mJoystickList.size();
  if (0 < initializedCount) {
    SDL_JoystickEventState(SDL_ENABLE);
    mInitialized = true;
    std::cout << "Initialized " << initializedCount << " joystick(s)." << std::endl;
  } else {
    mInitialized = false;
  }
}

