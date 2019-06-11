#ifndef OBJECT_LAYER_H
#define OBJECT_LAYER_H

#include <vector>
#include "GameObject.h"
#include "Layer.h"
#include "Vector2D.h"

class ObjectLayer : public Layer {
  public:
    ObjectLayer(void);
    virtual void render(void);
    virtual void update(void);
    std::vector<GameObject *> *getGameObjectList(void);

  private:
    std::vector<GameObject *> mGameObjectList;
};

#endif // OBJECT_LAYER_H

