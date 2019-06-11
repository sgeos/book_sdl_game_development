#include <string>
#include <vector>
#include "Level.h"

Level::Level(void) { }

Level::~Level(void) { }

void Level::render(void) {
  int size = mLayerList.size();
  for (int i = 0; i < size; i++) {
    mLayerList[i]->render();
  }
}

void Level::update(void) {
  int size = mLayerList.size();
  for (int i = 0; i < size; i++) {
    mLayerList[i]->update();
  }
}

std::vector<Tileset> *Level::getTilesetList(void) {
  return &mTilesetList;
}

std::vector<Layer *> *Level::getLayerList(void) {
  return &mLayerList;
}

