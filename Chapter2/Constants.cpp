#include "Constants.h"

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

namespace Constants {
  char const * const ApplicationName(void) {
    static const char result[] = "Chapter2";
    return result;
  }
  char const * const WindowTitle(void) {
    static const char result[] = "Chapter 2 - Textures!";
    return result;
  }
  std::string ResourcePath(const std::string &directory = "") {
    #ifdef _WIN32
      const char PATH_SEP = '\\';
    #else
      const char PATH_SEP = '/';
    #endif

    static std::string basePath;
    if (basePath.empty()) {
      char *sdlBasePath = SDL_GetBasePath();
      if (sdlBasePath) {
        basePath = sdlBasePath;
        SDL_free(sdlBasePath);
      } else {
        std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
        return "";
      }
      size_t replacePosition = basePath.rfind("bin");
      basePath = basePath.substr(0, replacePosition) + "res" + PATH_SEP;;
    }
    return directory.empty() ? basePath : basePath + directory + PATH_SEP;
  }
  int WindowPositionX(void) {
    return SDL_WINDOWPOS_CENTERED;
  }
  int WindowPositionY(void) {
    return SDL_WINDOWPOS_CENTERED;
  }
  int WindowWidth(void) {
    return 640;
  }
  int WindowHeight(void) {
    return 480;
  }
  int DefaultRendererWindow(void) {
    return -1;
  }
  int FramesPerSecond(void) {
    return 60;
  }
  int FrameWait(void) {
    return 1000 / FramesPerSecond();
  }
  int AnimationFrames(void) {
    return 6;
  }
}

