#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "LoaderParams.h"

class GameObject {
  public:
    GameObject(void) { }
    virtual ~GameObject(void) { }
    virtual void load(const LoaderParams *pParams) = 0;
    virtual void draw(void) = 0;
    virtual void update(void) = 0;
    virtual void cleanup(void) = 0;
};

#endif // GAME_OBJECT_H

