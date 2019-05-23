#include <iostream>
#include <string>
#include "Constants.h"
#include "DemoBackground.h"
#include "Enemy.h"
#include "Game.h"
#include "GameOverState.h"
#include "GameState.h"
#include "InputHandler.h"
#include "PlayState.h"
#include "PauseState.h"
#include "ShooterObject.h"
#include "Level.h"
#include "LevelParser.h"
#include "Vector2D.h"

const std::string PlayState::sStateId = "play";

void PlayState::update(void) {
  mLevel->update();
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
  int joypadId = 0;
  if (InputHandler::Instance()->isButtonDown(joypadId, 5) || InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE)) {
    Game::Instance()->getStateMachine()->pushState(new PauseState());
  } else {
    Game::Instance()->getStateMachine()->commitTransitionState();
  }
}

void PlayState::render(void) {
  mLevel->render();
  for (std::vector<GameObject *>::size_type i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

bool PlayState::onEnter(void) {
  LevelParser levelParser;
  mLevel = levelParser.parseLevel("test_map1.tmx");
  std::cout << "Entering state \"" << sStateId << "\"." << std::endl;
  return true;
}

bool PlayState::checkCollision(ShooterObject *pObjectA, ShooterObject *pObjectB) {
  int leftA, rightA, topA, bottomA;
  int leftB, rightB, topB, bottomB;

  leftA = pObjectA->getPosition().getX();
  rightA = leftA + pObjectA->getWidth();
  topA = pObjectA->getPosition().getY();
  bottomA = topA + pObjectA->getHeight();

  leftB = pObjectB->getPosition().getX();
  rightB = leftB + pObjectB->getWidth();
  topB = pObjectB->getPosition().getY();
  bottomB = topB + pObjectB->getHeight();

  return topA < bottomB && topB < bottomA && leftA < rightB && leftB < rightA;
}

