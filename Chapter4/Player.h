#ifndef PLAYER_H
#define PLAYER_H

#include "SdlGameObject.h"
#include "LoaderParams.h"

class Player : public SdlGameObject {
  public:
    Player(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
    void handleInput(void);

  private:
    int mAnimationFrames;
    int mBaseRotation;
};

#endif // PLAYER_H

