#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Constants.h"
#include "DemoBackgroundObject.h"
#include "ShooterObject.h"

DemoBackgroundObject::DemoBackgroundObject(void) : ShooterObject() { }

DemoBackgroundObject::~DemoBackgroundObject(void) { }

void DemoBackgroundObject::load(const std::unique_ptr<LoaderParams> &pParams) {
  ShooterObject::load(pParams);
}

void DemoBackgroundObject::draw(void) {
  ShooterObject::draw();
}

void DemoBackgroundObject::update(void) {
  ShooterObject::update();
  mVelocity.setX(5.0 * cos(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
  mVelocity.setY(5.0 * sin(M_PI * (double)mAnimationCounter / (double)Constants::FramesPerSecond()));
}

void DemoBackgroundObject::cleanup(void) { }

void DemoBackgroundObject::collision(void) { }

