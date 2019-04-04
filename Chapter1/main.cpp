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

bool init(SDL_Window *&pWindow, SDL_Renderer *&pRenderer) {
  if (0 != SDL_Init(SDL_INIT_VIDEO)) {
    logSdlError(std::cout, "SDL_Init");
    return false;
  }
  pWindow = SDL_CreateWindow(
    Constants::WindowTitle(),
    Constants::WindowPositionX(),
    Constants::WindowPositionY(),
    Constants::WindowWidth(),
    Constants::WindowHeight(),
    SDL_WINDOW_SHOWN
  );
  if (nullptr == pWindow) {
    logSdlError(std::cout, "SDL_CreateWindow");
    return false;
  }
  pRenderer = SDL_CreateRenderer(
    pWindow,
    Constants::DefaultRendererWindow(),
    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
  );
  if (nullptr == pRenderer) {
    logSdlError(std::cout, "SDL_CreateRenderer");
    return false;
  }
  return true;
}

void cleanup(SDL_Window *&pWindow, SDL_Renderer *&pRenderer) {
  Utility::cleanup(pRenderer, pWindow);
  SDL_Quit();
}

void frameToColor(int pFrame, int &pRed, int &pGreen, int &pBlue, int &pAlpha) {
  int framesPerCycle = 2.5 * Constants::FramesPerSecond();
  int hue = pFrame / framesPerCycle % 6;
  int intensity = 255 * abs(cos((float)pFrame / (2 * framesPerCycle) * M_PI));
  pAlpha = 255;
  switch (hue) {
    case 0:
      pRed =  255;
      pGreen = 0;
      pBlue = intensity;
      break;
    case 1:
      pRed = 255;
      pGreen = intensity;
      pBlue = 0;
      break;
    case 2:
      pRed = intensity;
      pGreen = 255;
      pBlue = 0;
      break;
    case 3:
      pRed = 0;
      pGreen = 255;
      pBlue = intensity;
      break;
    case 4:
      pRed = 0;
      pGreen = intensity;
      pBlue = 255;
      break;
    case 5:
      pRed = intensity;
      pGreen = 0;
      pBlue = 255;
      break;
  }
}

void render(SDL_Renderer *pRenderer, int pFrame) {
  int red, green, blue, alpha;
  frameToColor(pFrame, red, green, blue, alpha);
  SDL_SetRenderDrawColor(pRenderer, red, green, blue, alpha);
  SDL_RenderClear(pRenderer);
  SDL_RenderPresent(pRenderer);
  if (0 == pFrame % Constants::FramesPerSecond()) {
    std::cout << Constants::ApplicationName() << " Frame: " << pFrame << std::endl;
  }
}

void update(int &pFrame) {
  pFrame++;
}

void handleEvents(bool &pDone) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
      case SDL_MOUSEBUTTONDOWN:
      case SDL_KEYDOWN:
        pDone = true;
        break;
      default:
        break;
    }
  }
}

int main(int argc, char** argv) {
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  bool error = false == init(window, renderer);
  int frame = 0;
  bool done = error;
  while (!done) {
    handleEvents(done);
    update(frame);
    render(renderer, frame);
    SDL_Delay(Constants::FrameWait());
  }
  cleanup(window, renderer);
  return error ? EXIT_FAILURE : EXIT_SUCCESS;
}

