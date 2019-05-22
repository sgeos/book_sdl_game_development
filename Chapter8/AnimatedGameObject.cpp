#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "AnimatedGameObject.h"
#include "Constants.h"
#include "LoaderParams.h"
#include "ShooterObject.h"
#include "TextureManager.h"

AnimatedGameObject::AnimatedGameObject(void) : ShooterObject() { }

AnimatedGameObject::~AnimatedGameObject(void) { }

void AnimatedGameObject::load(const std::unique_ptr<LoaderParams> &pParams) {
  ShooterObject::load(pParams);
}

void AnimatedGameObject::draw(void) {
  ShooterObject::draw();
}

void AnimatedGameObject::update(void) {
  ShooterObject::update();
}

void AnimatedGameObject::cleanup(void) { }

void AnimatedGameObject::collision(void) { }

