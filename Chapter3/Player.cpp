#include <cmath>
#include <SDL2/SDL.h>

#include "Player.h"
#include "Constants.h"

void Player::load(int pX, int pY, int pWidth, int pHeight, std::string pTextureId) {
  GameObject::load(pX, pY, pWidth, pHeight, pTextureId);
}

void Player::draw(SDL_Renderer *pRenderer) {
  GameObject::draw(pRenderer);
}

void Player::update() {
  GameObject::update();
  mScale = 1.0 + cos((float)mAnimationCounter / Constants::FramesPerSecond());
}

void Player::cleanup() {}

