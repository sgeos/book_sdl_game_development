#ifndef DEMO_BACKGROUND_H
#define DEMO_BACKGROUND_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "LoaderParams.h"

class DemoBackground : public GameObject {
  public:
    DemoBackground(int pMaxIntensity = 255);
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void);
    virtual void collision(void);
    virtual std::string type(void) { return "DemoBackground"; }

  protected:
    std::string mTextureId;
    int mXOffset, mYOffset;
    int mTileWidth, mTileHeight;
    int mAnimationCounter;
    int mRed, mGreen, mBlue, mAlpha;
    int mMaxIntensity;
};

class DemoBackgroundCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new DemoBackground();
  }
};

#endif // DEMO_BACKGROUND_H

