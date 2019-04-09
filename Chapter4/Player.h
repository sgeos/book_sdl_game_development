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

  private:
    int mAnimationFrames;
};

#endif // PLAYER_H

