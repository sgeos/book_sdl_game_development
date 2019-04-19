#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

class GameState {
  public:
    virtual ~GameState(void) { }
    virtual void update(void) = 0;
    virtual void render(void) = 0;
    virtual bool onEnter(void) = 0;
    virtual bool onExit(void) = 0;
    virtual std::string getStateId(void) const = 0;
};

#endif // GAME_STATE_H

