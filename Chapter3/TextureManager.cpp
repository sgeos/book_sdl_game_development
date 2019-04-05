#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Log.h"
#include "TextureManager.h"

TextureManager *TextureManager::sInstance = nullptr;

bool TextureManager::load(std::string pFileName, std::string pId, SDL_Renderer *pRenderer) {
  SDL_Texture *texture = IMG_LoadTexture(pRenderer, pFileName.c_str());
  if (nullptr == texture) {
    Log::SdlError(std::cout, "LoadTexture");
    return false;
  }
  mTextureMap[pId] = texture;
  return texture;
  return true;
}

void TextureManager::draw(
  std::string pId,
  int pPositionX,
  int pPositionY,
  int pWidth,
  int pHeight,
  SDL_Renderer *pRenderer,
  double pScale,
  double pRotation,
  SDL_RendererFlip pFlip
) {
  drawFrame(pId, pPositionX, pPositionY, pWidth, pHeight, 0, 0, pRenderer, pScale, pRotation, pFlip);
}

void TextureManager::drawFrame(
  std::string pId,
  int pPositionX,
  int pPositionY,
  int pWidth,
  int pHeight,
  int pRow,
  int pFrame,
  SDL_Renderer *pRenderer,
  double pScale,
  double pRotation,
  SDL_RendererFlip pFlip
) {
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
  SDL_RenderCopyEx(pRenderer, mTextureMap[pId], &sourceRectangle, &destinationRectangle, pRotation, nullptr, pFlip);
}

int TextureManager::queryTexture(std::string pId, Uint32 *pFormat, int *pAccess, int *pWidth, int *pHeight) {
  return SDL_QueryTexture(mTextureMap[pId], pFormat, pAccess, pWidth, pHeight);
}

