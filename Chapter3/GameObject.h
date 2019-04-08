#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "LoaderParams.h"

class GameObject {
  public:
    GameObject(void) { }
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void cleanup() = 0;

  protected:
    GameObject(const LoaderParams *pParams) {}
    virtual ~GameObject() {}
};

#endif // GAME_OBJECT_H

