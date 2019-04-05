#ifndef UTILITY_H
#define UTILITY_H

#include <utility>
#include <SDL2/SDL.h>

namespace Utility {
  template<typename T, typename... Args>
  void cleanup(T *t, Args&&... args){
    cleanup(t);
    cleanup(std::forward<Args>(args)...);
  }
  template<>
  inline void cleanup<SDL_Window>(SDL_Window *window) {
    if (nullptr != window) {
      SDL_DestroyWindow(window);
    }
  }
  template<>
  inline void cleanup<SDL_Renderer>(SDL_Renderer *renderer) {
    if (nullptr != renderer) {
      SDL_DestroyRenderer(renderer);
    }
  }
  template<>
  inline void cleanup<SDL_Texture>(SDL_Texture *texture) {
    if (nullptr != texture) {
      SDL_DestroyTexture(texture);
    }
  }
  template<>
  inline void cleanup<SDL_Surface>(SDL_Surface *surface) {
    if (nullptr != surface) {
      SDL_FreeSurface(surface);
    }
  }
}

#endif // UTILITY_H

