#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <string>
#include "GameObject.h"
#include "TextureManager.h"

class GameState {
  public:
    virtual ~GameState(void) { }
    virtual std::string getStateId(void) const = 0;
    virtual void update(void) = 0;
    virtual void render(void) = 0;
    virtual bool onEnter(void) = 0;
    virtual bool onExit(void) {
      while (false == mGameObjectList.empty()) {
        delete mGameObjectList.back();
        mGameObjectList.pop_back();
      }
      int listSize = mTextureIdList.size();
      for (int i = 0; i < listSize; i++) {
        TextureManager::Instance()->unload(mTextureIdList[i]);
      }
      std::cout << "Exiting state \"" << getStateId() << "\"." << std::endl;
      return true;
    }

  protected:
    std::vector<GameObject *> mGameObjectList;
    std::vector<std::string> mTextureIdList;
};

#endif // GAME_STATE_H

