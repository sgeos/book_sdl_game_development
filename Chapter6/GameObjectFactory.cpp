#include <iostream>
#include <map>
#include <string>
#include "BaseCreator.h"
#include "GameObject.h"
#include "GameObjectFactory.h"

GameObjectFactory *GameObjectFactory::sInstance = nullptr;

bool GameObjectFactory::registerType(std::string pTypeId, BaseCreator *pCreator) {
  std::map<std::string, BaseCreator *>::iterator iterator = mCreatorList.find(pTypeId);
  bool success = mCreatorList.end() == iterator;
  if (success) {
    mCreatorList[pTypeId] = pCreator;
  } else {
    delete pCreator;
  }
  return success;
}

GameObject *GameObjectFactory::create(std::string pTypeId) {
  std::map<std::string, BaseCreator *>::iterator iterator = mCreatorList.find(pTypeId);
  bool success = mCreatorList.end() != iterator;
  GameObject *result;
  if (success) {
    BaseCreator *creator = (*iterator).second;
    result = creator->createGameObject();
  } else {
    std::cout << "GameObjectFactory::create missing type \"" << pTypeId << "\"." << std::endl;
    result = nullptr;
  }
  return result;
}

