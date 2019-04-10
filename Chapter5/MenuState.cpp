#include <iostream>
#include <string>
#include "MenuState.h"

const std::string MenuState::sStateId = "MENU";

void MenuState::update(void) {
  // TODO: add functionality
}

void MenuState::render(void) {
  // TODO: add functionality
}

bool MenuState::onEnter(void) {
  std::cout << "Entering MenuState \"" << sStateId << "\"." << std::endl;
  return true;
}

bool MenuState::onExit(void) {
  std::cout << "Exiting MenuState \"" << sStateId << "\"." << std::endl;
  return true;
}


