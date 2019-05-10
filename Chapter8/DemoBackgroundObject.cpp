#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Constants.h"
#include "DemoBackgroundObject.h"
#include "SdlGameObject.h"

DemoBackgroundObject::DemoBackgroundObject(void) { }

void DemoBackgroundObject::load(const LoaderParams *pParams) {
  SdlGameObject::load(pParams);
}

void DemoBackgroundObject::draw(void) {
  SdlGameObject::draw();
}

void DemoBackgroundObject::update(void) {
  SdlGameObject::update();
  mVelocity.setX(5.0 * cos(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  mVelocity.setY(5.0 * sin(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
}

void DemoBackgroundObject::cleanup(void) { }

