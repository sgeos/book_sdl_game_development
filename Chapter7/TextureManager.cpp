#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "Log.h"
#include "TextureManager.h"

TextureManager *TextureManager::sInstance = nullptr;

bool TextureManager::load(std::string pId, std::string pFileName) {
  SDL_Renderer *renderer = Game::Instance()->getRenderer();
  SDL_Texture *texture = IMG_LoadTexture(renderer, pFileName.c_str());
  if (nullptr == texture) {
    Log::SdlError(std::cout, "LoadTexture");
    return false;
  }
  if (nullptr != mTextureMap[pId]) {
    SDL_DestroyTexture(mTextureMap[pId]);
  }
  mTextureMap[pId] = texture;
  return true;
}

void TextureManager::unload(std::string pId) {
  mTextureMap.erase(pId);
}

void TextureManager::draw(
  std::string pId,
  int pPositionX,
  int pPositionY,
  int pWidth,
  int pHeight,
  double pScale,
  double pRotation,
  SDL_RendererFlip pFlip
) {
  drawFrame(pId, pPositionX, pPositionY, pWidth, pHeight, 0, 0, pScale, pRotation, pFlip);
}

void TextureManager::drawFrame(
  std::string pId,
  int pPositionX,
  int pPositionY,
  int pWidth,
  int pHeight,
  int pRow,
  int pFrame,
  double pScale,
  double pRotation,
  SDL_RendererFlip pFlip
) {
  SDL_Renderer *renderer = Game::Instance()->getRenderer();
  SDL_Rect sourceRectangle;
  sourceRectangle.x = pWidth * pFrame;
  sourceRectangle.y = pHeight * pRow;
  sourceRectangle.w = pWidth;
  sourceRectangle.h = pHeight;
  SDL_Rect destinationRectangle;
  destinationRectangle.x = pPositionX + (pWidth - pWidth * pScale) / 2;
  destinationRectangle.y = pPositionY + (pHeight - pHeight * pScale) / 2;
  destinationRectangle.w = pWidth * pScale;
  destinationRectangle.h = pHeight * pScale;
  SDL_RenderCopyEx(renderer, mTextureMap[pId], &sourceRectangle, &destinationRectangle, pRotation, nullptr, pFlip);
}

int TextureManager::queryTexture(std::string pId, Uint32 *pFormat, int *pAccess, int *pWidth, int *pHeight) {
  return SDL_QueryTexture(mTextureMap[pId], pFormat, pAccess, pWidth, pHeight);
}

