#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "Constants.h"
#include "DemoGameObject.h"
#include "PlatformerObject.h"
#include "TextureManager.h"

DemoGameObject::DemoGameObject(void) : PlatformerObject() { }

DemoGameObject::~DemoGameObject(void) { }

void DemoGameObject::load(const std::unique_ptr<LoaderParams> &pParams) {
  PlatformerObject::load(pParams);
}

void DemoGameObject::draw(void) {
  PlatformerObject::draw();
}

void DemoGameObject::update(void) {
  PlatformerObject::update();
  mScale = 1.0 - 0.5 * cos((float)mAnimationCounter / (Constants::FramesPerSecond() / 2));
  float dX = 2.0 * cos((float)mAnimationCounter / (2.0 * Constants::FramesPerSecond()));
  float dY = 2.0 * cos((float)mAnimationCounter / (1.0 * Constants::FramesPerSecond()));
  mVelocity.setX(dX);
  mVelocity.setY(dY);
  mRotation = 90 * cos((float)mAnimationCounter / (1.0 * Constants::FramesPerSecond()));;
  SDL_RendererFlip xFlip = 0.0 == dX ? (SDL_RendererFlip)(mFlip & SDL_FLIP_HORIZONTAL) : dX < 0.0 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
  SDL_RendererFlip yFlip = 0.0 == dY ? (SDL_RendererFlip)(mFlip & SDL_FLIP_VERTICAL) :  dY < 0.0 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE;
  mFlip = (SDL_RendererFlip)(xFlip | yFlip);
}

void DemoGameObject::cleanup(void) { }

void DemoGameObject::collision(void) { }

