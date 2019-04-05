#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "GameObject.h"

class Player : public GameObject {
  public:
    void load(int pX, int pY, int pWidth, int pHeight, std::string pTextureId);
    void draw(SDL_Renderer *pRenderer);
    void update();
    void cleanup();
};

#endif // PLAYER_H

