#include <iostream>
#include <string>
#include "Game.h"
#include "InputHandler.h"
#include "PlayState.h"

const std::string PlayState::sStateId = "PLAY";

void PlayState::update(void) {
  // TODO: add functionality
  int joypadId = 0;
  if (InputHandler::Instance()->isButtonDown(joypadId, 5) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    Game::Instance()->getStateMachine()->popState();
  }
}

void PlayState::render(void) {
  // TODO: add functionality
}

bool PlayState::onEnter(void) {
  std::cout << "Entering PlayState \"" << sStateId << "\"." << std::endl;
  return true;
}

bool PlayState::onExit(void) {
  std::cout << "Exiting PlayState \"" << sStateId << "\"." << std::endl;
  return true;
}


