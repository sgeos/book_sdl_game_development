#include <iostream>
#include <SDL2/SDL.h>

#include "Log.h"
#include "Constants.h"

namespace Log {
  void SdlError(std::ostream &pOutputStream, const std::string pMessage) {
    pOutputStream << Constants::ApplicationName() << " " << pMessage << " Error: " << SDL_GetError() << std::endl;
  }
}

