#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "AnimatedGameObject.h"
#include "Constants.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"
#include "TextureManager.h"

AnimatedGameObject::AnimatedGameObject(void) : PlatformerObject() { }

AnimatedGameObject::~AnimatedGameObject(void) { }

void AnimatedGameObject::load(const std::unique_ptr<LoaderParams> &pParams) {
  PlatformerObject::load(pParams);
}

void AnimatedGameObject::draw(void) {
  PlatformerObject::draw();
}

void AnimatedGameObject::update(void) {
  PlatformerObject::update();
}

void AnimatedGameObject::cleanup(void) { }

void AnimatedGameObject::collision(void) { }

