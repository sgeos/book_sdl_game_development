#ifndef GAME_H
#define GAME_H

#include <vector>

#include "GameObject.h"
#include "GameStateMachine.h"
#include "Player.h"
#include "TextureManager.h"

class Game {
  public:
    static Game *Instance(void) {
      if (nullptr == sInstance) {
        sInstance = new Game();
      }
      return sInstance;
    }
    ~Game(void);
    void cleanup(void);
    void reset(void);
    void render(void);
    void update(void);
    void handleEvents(void);
    void tick(void);
    int getFrame(void);
    SDL_Renderer *getRenderer(void);
    GameStateMachine *getStateMachine(void);
    int getWidth(void);
    int getHeight(void);
    void quit(void);
    bool isDone(void);
    bool isError(void);

  private:
    static Game *sInstance;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    GameStateMachine *mGameStateMachine;
    int mFrame;
    bool mDone;
    bool mError;

    Game(void);
};

#endif // GAME_H

