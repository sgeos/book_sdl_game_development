#include <cmath>
#include <SDL2/SDL.h>

#include "DemoPlayer.h"
#include "Constants.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "PlatformerObject.h"

DemoPlayer::DemoPlayer(void) :
  PlatformerObject(),
  mBaseRotation(0),
  mOrbitScale(1.0),
  mJoypadId(0),
  mTarget(0.0, 0.0),
  mTargetApproachSpeed(0)
{
  mScale = 1.5;
}

DemoPlayer::~DemoPlayer(void) { }

void DemoPlayer::load(const std::unique_ptr<LoaderParams> &pParams) {
  PlatformerObject::load(pParams);
}

void DemoPlayer::draw(void) {
  PlatformerObject::draw();
}

void DemoPlayer::handleInput(void) {
  InputHandler *inputHandler = InputHandler::Instance();
  if (inputHandler->isInitialized()) {
    if (inputHandler->isMouseButtonDown(LEFT)) {
      mTargetApproachSpeed = 1;
      mTarget.setX(inputHandler->getMousePosition()->getX());
      mTarget.setY(inputHandler->getMousePosition()->getY());
    } else if (inputHandler->isMouseButtonDown(MIDDLE)) {
      mTargetApproachSpeed = 0;
      mTarget.setX(inputHandler->getMousePosition()->getX());
      mTarget.setY(inputHandler->getMousePosition()->getY());
    } else if (inputHandler->isMouseButtonDown(RIGHT)) {
      mTargetApproachSpeed = -1;
      mTarget.setX(inputHandler->getMousePosition()->getX());
      mTarget.setY(inputHandler->getMousePosition()->getY());
    }
    float ddX = inputHandler->xValue(mJoypadId, 0) + inputHandler->xValue(mJoypadId, 1);
    float ddY = inputHandler->yValue(mJoypadId, 0) + inputHandler->yValue(mJoypadId, 1);
    if (inputHandler->isKeyDown(SDL_SCANCODE_RIGHT)) {
      ddX++;
    }
    if (inputHandler->isKeyDown(SDL_SCANCODE_LEFT)) {
      ddX--;
    }
    if (inputHandler->isKeyDown(SDL_SCANCODE_DOWN)) {
      ddY++;
    }
    if (inputHandler->isKeyDown(SDL_SCANCODE_UP)) {
      ddY--;
    }
    if (0 != ddY && mBaseRotation < 90 && -90 < mBaseRotation) {
      mBaseRotation += ddY;
    } else if (0 == ddY && 0 < mBaseRotation) {
      mBaseRotation--;
    } else if (0 == ddY && mBaseRotation < 0) {
      mBaseRotation++;
    }
    if (0 == ddY && 0 == ddX) {
      Vector2D targetMovement = (mTarget - mPosition) * mTargetApproachSpeed;
      targetMovement.normalize();
      ddX = targetMovement.getX();
      ddY = targetMovement.getY();
    }
    mAcceleration.setX(ddX);
    mAcceleration.setY(ddY);
  }
  if (inputHandler->isButtonDown(mJoypadId, 0)) {
    mScale -= 0.01;
  } else if (inputHandler->isButtonDown(mJoypadId, 1)) {
    mScale += 0.01;
  }
  if (inputHandler->isButtonDown(mJoypadId, 2)) {
    mOrbitScale += 0.01;
  } else if (inputHandler->isButtonDown(mJoypadId, 3)) {
    mOrbitScale -= 0.01;
  }
}

void DemoPlayer::update(void) {
  PlatformerObject::update();
  handleInput();
  mScale += (-1.0 / 60.0) * sin((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dX = 2.5 * mOrbitScale * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dY = 1.0 * mOrbitScale * sin((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  mVelocity.setX(dX);
  mVelocity.setY(dY);
  float ddX = mAcceleration.getX();
  ddX += 0.0 == ddX ? dX : 0.0;
  mFlip = 0.0 == ddX ? mFlip : ddX < 0.0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  mRotation = SDL_FLIP_HORIZONTAL != (mFlip & SDL_FLIP_HORIZONTAL) ? mBaseRotation : -mBaseRotation;
}

void DemoPlayer::cleanup(void) { }

void DemoPlayer::collision(void) { }

