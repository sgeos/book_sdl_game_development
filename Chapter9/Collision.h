#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include "Vector2D.h"

const static int sBuffer = 4;

static bool RectangleRectangle(SDL_Rect* pRectangleA, SDL_Rect* pRectangleB)
{
  int widthOffset = (pRectangleA->w + pRectangleB->w) / sBuffer;
  int heightOffset = (pRectangleA->h + pRectangleB->h) / sBuffer;
  return    
    pRectangleB->y < pRectangleA->y + pRectangleA->h - heightOffset &&
    pRectangleA->y < pRectangleB->y + pRectangleB->h - heightOffset &&
    pRectangleB->x < pRectangleA->x + pRectangleA->w - widthOffset &&
    pRectangleA->x < pRectangleB->x + pRectangleB->w - widthOffset;
}

#endif // COLLISION_H

