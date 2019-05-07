#ifndef GAME_OBJECT_FACTORY_H
#define GAME_OBJECT_FACTORY_H

#include <map>
#include <string>
#include "BaseCreator.h"
#include "GameObject.h"

class GameObjectFactory {
  public:
    static GameObjectFactory *Instance(void) {
      if (nullptr == sInstance) {
        sInstance = new GameObjectFactory();
      }
      return sInstance;
    }
    bool registerType(std::string pTypeId, BaseCreator *pCreator);
    GameObject *create(std::string pTypeId);

  private:
    static GameObjectFactory *sInstance;
    std::map<std::string, BaseCreator *> mCreatorList;
};

#endif // GAME_OBJECT_FACTORY_H

