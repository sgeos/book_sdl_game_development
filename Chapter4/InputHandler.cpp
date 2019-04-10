#include <SDL2/SDL.h>
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "Vector2D.h"

InputHandler *InputHandler::sInstance;

InputHandler::InputHandler(void) { }

void InputHandler::reset(void) {
  while (false == mJoystickList.empty()) {
    SDL_JoystickClose(mJoystickList.back());
    mJoystickList.pop_back();
  }
  while (false == mJoystickAxisList.empty()) {
    delete mJoystickAxisList.back().first;
    delete mJoystickAxisList.back().second;
    mJoystickAxisList.pop_back();
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
      case SDL_JOYAXISMOTION:
      {
        int result;
        if (mJoystickDeadZone < event.jaxis.value) {
          result = 1;
        } else if (event.jaxis.value < -mJoystickDeadZone) {
          result = -1;
        } else /* -deadZone <= value <= deadZone */ {
          result = 0;
        }
        int deviceId = event.jaxis.which;
        int axisId = event.jaxis.axis;
        switch (axisId % 4) {
          default:
          case 0:
            mJoystickAxisList[deviceId].first->setX(result);
            break;
          case 1:
            mJoystickAxisList[deviceId].first->setY(result);
            break;
          case 2:
            mJoystickAxisList[deviceId].second->setX(result);
            break;
          case 3:
            mJoystickAxisList[deviceId].second->setY(result);
            break;
        }
        // std::cout << "Joy Axis Motion: Device " << deviceId << ", Axis " << axisId;
        // std::cout << ", Value: " << event.jaxis.value << ", Result: " << result << std::endl;
        break;
      }
      case SDL_JOYBUTTONDOWN:
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
  if (0 < joystickCount) {
    SDL_JoystickEventState(SDL_ENABLE);
  }
  for (int i = 0; i < joystickCount; i++) {
    SDL_Joystick *joystick = SDL_JoystickOpen(i);
    if (joystick) {
      mJoystickList.push_back(joystick);
      mJoystickAxisList.push_back(std::make_pair(new Vector2D(0.0, 0.0), new Vector2D(0.0, 0.0)));
      std::cout << "Initialized joystick " << i << " \"" << SDL_JoystickName(mJoystickList[i]) << "\"." << std::endl;
    } else {
      Log::SdlError(std::cout, "SDL_JoystickOpen");
    }
  }
  int initializedCount = mJoystickList.size();
  if (0 < initializedCount) {
    mInitialized = true;
    std::cout << "Total joystick count: " << initializedCount << std::endl;
  } else {
    mInitialized = false;
    std::cout << "Joystick initialization failed." << std::endl;
  }
}

int InputHandler::xValue(int pDeviceId, int pAxisId) {
  int result = 0;
  if (pDeviceId < mJoystickList.size()) {
    switch (pAxisId) {
      default:
      case 0:
        result = mJoystickAxisList[pDeviceId].first->getX();
        break;
      case 1:
        result = mJoystickAxisList[pDeviceId].second->getX();
        break;
    }
  }
  return result;
}

int InputHandler::yValue(int pDeviceId, int pAxisId) {
  int result = 0;
  if (pDeviceId < mJoystickList.size()) {
    switch (pAxisId) {
      default:
      case 0:
        result = mJoystickAxisList[pDeviceId].first->getY();
        break;
      case 1:
        result = mJoystickAxisList[pDeviceId].second->getY();
        break;
    }
  }
  return result;
}

