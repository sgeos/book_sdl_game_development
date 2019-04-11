#ifndef DEMO_BACKGROUND_OBJECT_H
#define DEMO_BACKGROUND_OBJECT_H

#include "SdlGameObject.h"
#include "LoaderParams.h"

class DemoBackgroundObject : public SdlGameObject {
  public:
    DemoBackgroundObject(const LoaderParams *pParams);
    void draw(void);
    void update(void);
    void cleanup(void);
};

#endif // DEMO_BACKGROUND_OBJECT_H

