#include <vector>
#include "GameObject.h"
#include "ObjectLayer.h"
#include "Vector2D.h"

ObjectLayer::ObjectLayer(void) {
}

void ObjectLayer::render(void) {
  for (int i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->draw();
  }
}

void ObjectLayer::update(void) {
  for (int i = 0; i < mGameObjectList.size(); i++) {
    mGameObjectList[i]->update();
  }
}

std::vector<GameObject *> *ObjectLayer::getGameObjectList(void) {
  return &mGameObjectList;
}

