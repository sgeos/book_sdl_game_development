#include <cmath>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Constants.h"
#include "SdlGameObject.h"

Player::Player(const LoaderParams *pParams) : SdlGameObject(pParams) { }

void Player::draw(void) {
  SdlGameObject::draw();
}

void Player::update(void) {
  SdlGameObject::update();
  mScale = 1.0 + cos((float)mAnimationCounter / Constants::FramesPerSecond());
}

void Player::cleanup(void) { }

