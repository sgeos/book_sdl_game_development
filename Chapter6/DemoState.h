#ifndef DEMO_STATE_H
#define DEMO_STATE_H

#include <string>
#include <vector>
#include "GameState.h"
#include "GameObject.h"

class DemoState : public GameState {
  public:
    virtual void update(void);
    virtual void render(void);
    virtual bool onEnter(void);
    virtual std::string getStateId(void) const { return sStateId; }

  private:
    static const std::string sStateId;
};

#endif // DEMO_STATE_H

