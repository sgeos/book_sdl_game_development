#ifndef ENEMY_H
#define ENEMY_H

#include "SdlGameObject.h"
#include "LoaderParams.h"

class Enemy : public SdlGameObject {
  public:
    Enemy(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
};

#endif // ENEMY_H

