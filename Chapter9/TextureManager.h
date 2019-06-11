#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include <SDL2/SDL.h>

class TextureManager {
  public:
    static TextureManager *Instance(void) {
      if (nullptr == sInstance) {
        sInstance = new TextureManager();
      }
      return sInstance;
    }
    bool load(std::string pId, std::string pFileName);
    void unload(std::string pId);
    void draw(
      std::string pId,
      int pPositionX,
      int pPositionY,
      int pWidth,
      int pHeight,
      double pScale = 1.0,
      double pRotation = 0.0,
      double pAlpha = 1.0,
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
      double pScale = 1.0,
      double pRotation = 0.0,
      double pAlpha = 1.0,
      SDL_RendererFlip pFlip = SDL_FLIP_NONE
    );
    void drawTile(
      std::string pId,
      int pMargin,
      int pSpacing,
      int pPositionX,
      int pPositionY,
      int pWidth,
      int pHeight,
      int pRow,
      int pFrame
    );
    void drawRaw(
      std::string pId,
      const SDL_Rect *pSource,
      const SDL_Rect *pDestination
    );
    int queryTexture(std::string pId, Uint32 *pFormat, int *pAccess, int *pWidth, int *pHeight);

  private:
    static TextureManager *sInstance;
    std::map<std::string, SDL_Texture *> mTextureMap;

    TextureManager() {}
};

#endif // TEXTURE_MANAGER_H

