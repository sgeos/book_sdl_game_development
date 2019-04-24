#include <SDL2/SDL.h>
#include "Game.h"
#include "InputHandler.h"
#include "Log.h"
#include "Vector2D.h"

InputHandler *InputHandler::sInstance;

InputHandler::InputHandler(void) : mMousePosition(0.0, 0.0) {
  for (int i = 0; i < 3; i++) {
    mMouseButtonList.push_back(false);
  }
  onKeyEvent();
}

InputHandler::~InputHandler(void) {
  reset();
}

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

void InputHandler::onJoystickAxisMotionEvent(int pDeviceId, int pAxisId, int pAxisValue) {
  int result;
  if (mJoystickDeadZone < pAxisValue) {
    result = 1;
  } else if (pAxisValue < -mJoystickDeadZone) {
    result = -1;
  } else /* -mJoystickDeadZone <= pAxisValue <= mJoystickDeadZone */ {
    result = 0;
  }
  switch (pAxisId % 4) {
    default:
    case 0:
      mJoystickAxisList[pDeviceId].first->setX(result);
      break;
    case 1:
      mJoystickAxisList[pDeviceId].first->setY(result);
      break;
    case 2:
      mJoystickAxisList[pDeviceId].second->setX(result);
      break;
    case 3:
      mJoystickAxisList[pDeviceId].second->setY(result);
      break;
  }
  // std::cout << "Joy Axis Motion: Device " << pDeviceId << ", Axis " << pAxisId;
  // std::cout << ", Value: " << pAxisValue << ", Result: " << result << std::endl;
}

void InputHandler::onJoystickButtonEvent(int pDeviceId, int pButtonId, int pIsDown) {
  mJoystickButtonList[pDeviceId][pButtonId] = pIsDown;
}

void InputHandler::onMouseMotionEvent(int pX, int pY) {
  mMousePosition.setX(pX);
  mMousePosition.setY(pY);
}

void InputHandler::onMouseButtonEvent(int pSdlButtonId, bool pIsDown) {
  int buttonId;
  switch (pSdlButtonId) {
    default:
    case SDL_BUTTON_LEFT:
      buttonId = LEFT;
      break;
    case SDL_BUTTON_MIDDLE:
      buttonId = MIDDLE;
      break;
    case SDL_BUTTON_RIGHT:
      buttonId = RIGHT;
      break;
  }
  mMouseButtonList[buttonId] = pIsDown;
}

void InputHandler::onKeyEvent(void) {
  mKeyState = SDL_GetKeyboardState(nullptr);
}

void InputHandler::update(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        Game::Instance()->quit();
        break;
      case SDL_JOYAXISMOTION:
        onJoystickAxisMotionEvent(event.jaxis.which, event.jaxis.axis, event.jaxis.value);
        break;
      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        onJoystickButtonEvent(event.jaxis.which, event.jbutton.button, SDL_JOYBUTTONDOWN == event.type);
        break;
      case SDL_MOUSEMOTION:
        onMouseMotionEvent(event.motion.x, event.motion.y);
        break;
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEBUTTONDOWN:
        onMouseButtonEvent(event.button.button, SDL_MOUSEBUTTONDOWN == event.type);
        break;
      case SDL_KEYUP:
      case SDL_KEYDOWN:
        onKeyEvent();
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
      std::vector<bool> buttonSet;
      int buttonCount = SDL_JoystickNumButtons(joystick);
      for (int i = 0; i < buttonCount; i++) {
        buttonSet.push_back(false);
      }
      mJoystickButtonList.push_back(buttonSet);
      std::cout << "Initialized " << SDL_JoystickNumAxes(joystick) << " axis " << buttonCount << " button joystick ";
      std::cout << i << " \"" << SDL_JoystickName(mJoystickList[i]) << "\"." << std::endl;
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

bool InputHandler::isButtonDown(int pDeviceId, int pButtonId) {
  return pDeviceId < mJoystickButtonList.size() ? mJoystickButtonList[pDeviceId][pButtonId] : false;
}

Vector2D *InputHandler::getMousePosition(void) {
  return &mMousePosition;
}

bool InputHandler::isMouseButtonDown(int pButtonId) {
  return mMouseButtonList[pButtonId];
}

bool InputHandler::isKeyDown(SDL_Scancode pScancode) {
  if (nullptr != mKeyState) {
    return 0 != mKeyState[pScancode];
  }
  return false;
}

