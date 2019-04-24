#define _USE_MATH_DEFINES
#include <cmath>
#include <SDL2/SDL.h>
#include "AnimatedGameObject.h"
#include "Constants.h"
#include "LoaderParams.h"
#include "SdlGameObject.h"
#include "TextureManager.h"

AnimatedGameObject::AnimatedGameObject(void) : SdlGameObject(), mAnimationSpeed(1), mAnimationFrames(1) { }

void AnimatedGameObject::load(const LoaderParams *pParams)
{
  SdlGameObject::load(pParams);
  mAnimationSpeed = pParams->getAnimationSpeed();
  mAnimationFrames = pParams->getAnimationFrames();
  if (0 == mAnimationFrames) {
    TextureManager::Instance()->queryTexture(mTextureId, nullptr, nullptr, &mAnimationFrames, nullptr);
    mAnimationFrames /= mWidth;
  }
}

void AnimatedGameObject::draw(void) {
  SdlGameObject::draw();
}

void AnimatedGameObject::update(void) {
  SdlGameObject::update();
  mAnimationFrame = (mAnimationCounter / (1000 / mAnimationSpeed)) % mAnimationFrames;
}

void AnimatedGameObject::cleanup(void) { }

