#include "Camera.h"
#include "Game.h"
#include "Vector2D.h"

Camera *Camera::sInstance = new Camera();

Camera::Camera(void) : mPosition(0.0f, 0.0f), mTarget(nullptr) { }

Camera::~Camera(void) {
  delete mTarget;
}

void Camera::update(Vector2D pVelocity) {
  mPosition += pVelocity;
  if (mPosition.getX() < 0) {
    mPosition.setX(0);
  }
}

const Vector2D Camera::getPosition(void) const {
  if (nullptr != mTarget) {
    Vector2D position(mTarget->getX() - (Game::Instance()->getWidth() / 2), 0.0f);
    if (position.getX() < 0) {
      position.setX(0);
    }
    return position;
  }
  return mPosition;
}

