#ifndef GAME_H
#define GAME_H

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
    SDL_Texture *mTexture;
    SDL_Texture *mBackground;
    SDL_Rect mSourceRectangle, mDestinationRectangle;
    int mFrame;
    bool mDone;
    bool mError;
    int mRed, mGreen, mBlue, mAlpha;
};

#endif // GAME_H

