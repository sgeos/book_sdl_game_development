#ifndef DEMO_BACKGROUND_H
#define DEMO_BACKGROUND_H

#include "GameObject.h"
#include "LoaderParams.h"

class DemoBackground : public GameObject {
  public:
    DemoBackground(const LoaderParams *pParams, int pMaxIntensity = 255);
    virtual void draw();
    virtual void update();
    virtual void cleanup();

  protected:
    std::string mTextureId;
    int mXOffset, mYOffset;
    int mTileWidth, mTileHeight;
    int mAnimationCounter;
    int mRed, mGreen, mBlue, mAlpha;
    int mMaxIntensity;
};

#endif // DEMO_BACKGROUND_H

