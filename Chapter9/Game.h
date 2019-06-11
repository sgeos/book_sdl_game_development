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
    void setPlayerLives(int pPlayerLives) { mPlayerLives = pPlayerLives; }
    int getPlayerLives(void) { return mPlayerLives; }
    void setCurrentLevel(int pCurrentLevel);
    const int getCurrentLevel(void) { return mCurrentLevel; }
    void setNextLevel(int pNextLevel) { mNextLevel = pNextLevel; }
    const int getNextLevel(void) { return mNextLevel; }
    void setLevelComplete(int pLevelComplete) { mLevelComplete = pLevelComplete; }
    const bool getLevelComplete(void) { return mLevelComplete; }
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
    int mPlayerLives;
    int mCurrentLevel;
    int mNextLevel;
    bool mLevelComplete;
    int mFrame;
    bool mDone;
    bool mError;

    Game(void);
};

#endif // GAME_H

