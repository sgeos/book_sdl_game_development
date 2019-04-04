#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

#include "Constants.h"
#include "Utility.h"

void logSdlError(std::ostream &pOutputStream, const std::string pMessage) {
  pOutputStream << Constants::ApplicationName() << " " << pMessage << " Error: " << SDL_GetError() << std::endl;
}

int main(int argc, char** argv) {
  if (0 != SDL_Init(SDL_INIT_VIDEO)) {
    logSdlError(std::cout, "SDL_Init");
    return EXIT_FAILURE;
  }
  SDL_Window *window = SDL_CreateWindow(
    Constants::WindowTitle(),
    Constants::WindowPositionX(),
    Constants::WindowPositionY(),
    Constants::WindowWidth(),
    Constants::WindowHeight(),
    SDL_WINDOW_SHOWN
  );
  if (nullptr == window) {
    logSdlError(std::cout, "SDL_CreateWindow");
    SDL_Quit();
    return EXIT_FAILURE;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(
    window,
    Constants::DefaultRendererWindow(),
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (nullptr == renderer) {
    logSdlError(std::cout, "SDL_CreateRenderer");
    Utility::cleanup(window);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  bool done = false;
  int frame = 0;
  do {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
        case SDL_MOUSEBUTTONDOWN:
        case SDL_KEYDOWN:
          done = true;
          break;
        default:
          break;
      }
    }
    int framesPerCycle = 2.5 * Constants::FramesPerSecond();
    int hue = frame / framesPerCycle % 6;
    int intensity = 255 * abs(cos((float)frame / (2 * framesPerCycle) * M_PI));
    int red, green, blue, alpha;
    alpha = 255;
    switch (hue) {
      case 0:
        red =  255;
        green = 0;
        blue = intensity;
        break;
      case 1:
        red = 255;
        green = intensity;
        blue = 0;
        break;
      case 2:
        red = intensity;
        green = 255;
        blue = 0;
        break;
      case 3:
        red = 0;
        green = 255;
        blue = intensity;
        break;
      case 4:
        red = 0;
        green = intensity;
        blue = 255;
        break;
      case 5:
        red = intensity;
        green = 0;
        blue = 255;
        break;
    }
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    if (0 == frame % Constants::FramesPerSecond()) {
      std::cout << Constants::ApplicationName() << " Frame: " << frame << std::endl;
    }
    frame++;
    SDL_Delay(Constants::FrameWait());
  } while (!done);
  Utility::cleanup(renderer, window);
  SDL_Quit();
  return EXIT_SUCCESS;
}

