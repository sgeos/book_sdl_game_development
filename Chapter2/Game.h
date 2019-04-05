#ifndef GAME_H
#define GAME_H

#include "TextureManager.h"

class Game {
  public:
    Game(void);
    ~Game(void);
    void cleanup(void);
    void reset(void);
    void render(void);
    void update(void);
    void handleEvents(void);
    void tick(void);
    int getFrame(void);
    bool isDone(void);
    bool isError(void);

  private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    int mFrame;
    bool mDone;
    bool mError;
    int mRed, mGreen, mBlue, mAlpha;
    int mObjectX, mObjectY;
    double mObjectScale, mObjectRotation;
    int mObjectAnimationFrame;
    TextureManager *mTextureManager;
};

#endif // GAME_H

