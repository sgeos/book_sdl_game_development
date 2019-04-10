#include <iostream>
#include <string>
#include "PlayState.h"

const std::string PlayState::sStateId = "PLAY";

void PlayState::update(void) {
  // TODO: add functionality
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


