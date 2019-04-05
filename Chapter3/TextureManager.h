#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <SDL2/SDL.h>

class TextureManager {
  public:
    static TextureManager *Instance() {
      if (nullptr == sInstance) {
        sInstance = new TextureManager();
      }
      return sInstance;
    }
    bool load(std::string pFileName, std::string pId, SDL_Renderer *pRenderer);
    void draw(
      std::string pId,
      int pPositionX,
      int pPositionY,
      int pWidth,
      int pHeight,
      SDL_Renderer *pRenderer,
      double pScale = 1.0,
      double pRotation = 0.0,
      SDL_RendererFlip pFlip = SDL_FLIP_NONE
    );
    void drawFrame(
      std::string pId,
      int pPositionX,
      int pPositionY,
      int pWidth,
      int pHeight,
      int pRow,
      int pFrame,
      SDL_Renderer *pRenderer,
      double pScale = 1.0,
      double pRotation = 0.0,
      SDL_RendererFlip pFlip = SDL_FLIP_NONE
    );
    int queryTexture(std::string pId, Uint32 *pFormat, int *pAccess, int *pWidth, int *pHeight);

  private:
    static TextureManager *sInstance;
    std::map<std::string, SDL_Texture *> mTextureMap;

    TextureManager() {}
};

#endif // TEXTURE_MANAGER_H

