#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Log.h"
#include "TextureManager.h"

TextureManager *TextureManager::sInstance = nullptr;

bool TextureManager::load(SDL_Renderer *pRenderer, std::string pId, std::string pFileName) {
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
  SDL_Renderer *pRenderer,
  std::string pId,
  int pPositionX,
  int pPositionY,
  int pWidth,
  int pHeight,
  double pScale,
  double pRotation,
  SDL_RendererFlip pFlip
) {
  drawFrame(pRenderer, pId, pPositionX, pPositionY, pWidth, pHeight, 0, 0, pScale, pRotation, pFlip);
}

void TextureManager::drawFrame(
  SDL_Renderer *pRenderer,
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

