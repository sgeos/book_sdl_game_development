#ifndef SCROLLING_BACKGROUND_H
#define SCROLLING_BACKGROUND_H

#include "BaseCreator.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include "PlatformerObject.h"

class ScrollingBackground : public PlatformerObject {
  public:
    ScrollingBackground(void);
    virtual ~ScrollingBackground(void) { }
    virtual void load(const std::unique_ptr<LoaderParams> &pParams);
    virtual void draw(void);
    virtual void update(void);
    virtual void cleanup(void);

  private:
    int mScrollSpeed;
    int mCount;
    int mMaxCount;
    SDL_Rect mSourceRectangleA;
    SDL_Rect mSourceRectangleB;
    SDL_Rect mDestinationRectangleA;
    SDL_Rect mDestinationRectangleB;
    void reset(void);
};

class ScrollingBackgroundCreator : public BaseCreator {
  GameObject *createGameObject(void) const {
    return new ScrollingBackground();
  }
};

#endif // SCROLLING_BACKGROUND_H

