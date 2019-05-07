#include "SdlGameObject.h"
#include "InputHandler.h"
#include "LoaderParams.h"
#include "MenuButton.h"

MenuButton::MenuButton(void) : mCallback(nullptr) {
  mAnimationFrame = MOUSE_OUT;
}

void MenuButton::load(const LoaderParams *pParams) {
  SdlGameObject::load(pParams);
  mCallbackId = pParams->getCallbackId();
}

void MenuButton::draw(void) {
  SdlGameObject::draw();
}

void MenuButton::update(void) {
  SdlGameObject::update();
  const Vector2D *mousePosition = InputHandler::Instance()->getMousePosition();
  const int mouseX = mousePosition->getX();
  const int mouseY = mousePosition->getY();
  const int x = mPosition.getX();
  const int y = mPosition.getY();
  const int w = mWidth;
  const int h = mHeight;
  const bool outOfBounds = mouseX < x || (x + w) < mouseX || mouseY < y || (y + h) < mouseY;
  if (outOfBounds) {
    mAnimationFrame = MOUSE_OUT;
    mWasClicked = false;
    mRunCallback = false;
  } else {
    const bool isClicked = InputHandler::Instance()->isMouseButtonDown(LEFT);
    if (false == mWasOutOfBounds && false == mWasClicked && true == isClicked) {
      mRunCallback = true;
    }
    if (true == mRunCallback && false == isClicked && nullptr != mCallback) {
      mCallback();
      mRunCallback = false;
    }
    mAnimationFrame = mRunCallback ? CLICKED : MOUSE_OVER;
    mWasClicked = isClicked;
  }
  mWasOutOfBounds = outOfBounds;
}

void MenuButton::cleanup(void) {
  SdlGameObject::cleanup();
}

void MenuButton::setCallback(void (*pCallback)(void)) {
  mCallback = pCallback;
}

int MenuButton::getCallbackId(void) {
  return mCallbackId;
}

