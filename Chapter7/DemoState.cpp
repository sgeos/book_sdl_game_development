#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "Constants.h"
#include "DemoBackground.h"
#include "DemoGameObject.h"
#include "DemoPlayer.h"
#include "DemoState.h"
#include "DemoBackgroundObject.h"
#include "Game.h"
#include "InputHandler.h"
#include "PauseState.h"
#include "StateParser.h"
#include "TextureManager.h"

const std::string DemoState::sStateId = "demo";

void DemoState::update(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  int joypadId = 0;
  if (InputHandler::Instance()->isButtonDown(joypadId, 5) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    Game::Instance()->getStateMachine()->pushState(new PauseState());
  }
}

void DemoState::render(void) {
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool DemoState::onEnter(void) {
  StateParser stateParser;
  stateParser.parseState("demo.xml", sStateId, &mGameObjectList, &mTextureIdList);
  std::cout << "Entering state \"" << sStateId << "\"." << std::endl;
  return true;
}

