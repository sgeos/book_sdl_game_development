#ifndef BASE_CREATOR_H
#define BASE_CREATOR_H

#include "GameObject.h"

class BaseCreator {
  public:
    virtual GameObject *createGameObject(void) const = 0;
    virtual ~BaseCreator(void) { }
};

#endif // BASE_CREATOR_H

