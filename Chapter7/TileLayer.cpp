#include <iostream>
#include <vector>
#include "Game.h"
#include "Level.h"
#include "TextureManager.h"
#include "TileLayer.h"

TileLayer::TileLayer(int pTileSize, const std::vector<Tileset> &pTilesetList) :
  mTileSize(pTileSize),
  mPosition(0.0f, 0.0f),
  mVelocity(0.0f, 0.0f),
  mTilesetList(pTilesetList)
{
  mColumnCount = Game::Instance()->getWidth() / mTileSize;
  mRowCount = Game::Instance()->getHeight() / mTileSize;
}

void TileLayer::render(void) {
  int xIndex = mPosition.getX() / mTileSize;
  int yIndex = mPosition.getY() / mTileSize;
  int xOffset = int(mPosition.getX()) % mTileSize;
  int yOffset = int(mPosition.getY()) % mTileSize;
  for (int i = 0; i < mRowCount; i++) {
    for (int j = 0; j < mColumnCount; j++) {
      int id = mTileIdList[i + yIndex][j + xIndex];
      if (0 == id) {
        continue;
      }
      Tileset tileset = getTilesetById(id);
      id--;
      TextureManager::Instance()->drawTile(
        tileset.name,
        tileset.margin,
        tileset.spacing,
        (j * mTileSize) - xOffset,
        (i * mTileSize) - yOffset,
        mTileSize,
        mTileSize,
        (id - (tileset.firstGridId - 1)) / tileset.columnCount,
        (id - (tileset.firstGridId - 1)) % tileset.columnCount
      );
    }
  }
}

void TileLayer::update(void) {
  mPosition += mVelocity;
}

void TileLayer::setTileIds(const std::vector<std::vector<int>> &pTileIdList) {
  mTileIdList = pTileIdList;
}

void TileLayer::setTileSize(int pTileSize) {
  mTileSize = pTileSize;
}

Tileset TileLayer::getTilesetById(int pTileId) {
  for (int i = 0; i < mTilesetList.size(); i++) {
    if ( i + 1 <= mTilesetList.size() - 1
      && mTilesetList[i].firstGridId <= pTileId
      && pTileId < mTilesetList[i + 1].firstGridId
    ) {
      return mTilesetList[i];
    }
  }
  if (0 < mTilesetList.size()) {
    return mTilesetList[mTilesetList.size() - 1];
  } else {
    std::cout << "Did not find tileset for tile id = " << pTileId << ", returning empty tileset." << std::endl;
    Tileset result;
    return result;
  }
}

