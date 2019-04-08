#ifndef DEMO_GAME_OBJECT_H
#define DEMO_GAME_OBJECT_H

#include "SdlGameObject.h"
#include "LoaderParams.h"

class DemoGameObject : public SdlGameObject {
  public:
    DemoGameObject(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);

  private:
    int mAnimationFrames;
    int mCenterX, mCenterY;
};

#endif // DEMO_GAME_OBJECT_H

