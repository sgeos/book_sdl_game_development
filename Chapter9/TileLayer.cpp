#include <iostream>
#include <vector>
#include "Camera.h"
#include "Game.h"
#include "Level.h"
#include "TextureManager.h"
#include "TileLayer.h"

TileLayer::TileLayer(int pTileSize, int pMapWidth, int pMapHeight, const std::vector<struct Tileset> &pTilesetList) :
  mColumnCount(pMapWidth),
  mRowCount(pMapHeight),
  mTileSize(pTileSize),
  mMapWidth(pMapWidth),
  mPosition(0.0f, 0.0f),
  mVelocity(0.0f, 0.0f),
  mTilesetList(pTilesetList)
{ }

void TileLayer::render(void) {
  int xIndex = mPosition.getX() / mTileSize;
  int yIndex = mPosition.getY() / mTileSize;
  int xOffset = int(mPosition.getX()) % mTileSize;
  int yOffset = int(mPosition.getY()) % mTileSize;
  int rowMax = mRowCount + 1;
  int columnMax = mColumnCount + 1;
  for (int i = 0; i < rowMax; i++) {
    for (int j = 0; j < columnMax; j++) {
      int defaultTile = 0;
      int id = getTileIdByPosition(j + xIndex, i + yIndex, defaultTile);
      if (0 == id) {
        continue;
      }
      int tileX = j * mTileSize - xOffset - Camera::Instance()->getPosition().getX();
      int tileY = i * mTileSize - yOffset - Camera::Instance()->getPosition().getY();
      if (tileX < -mTileSize || Game::Instance()->getWidth() < tileX) {
        continue;
      }
      Tileset tileset = getTilesetById(id);
      id--;
      TextureManager::Instance()->drawTile(
        tileset.name,
        tileset.margin,
        tileset.spacing,
        tileX,
        tileY,
        mTileSize,
        mTileSize,
        (id - (tileset.firstGridId - 1)) / tileset.columnCount,
        (id - (tileset.firstGridId - 1)) % tileset.columnCount
      );
    }
  }
}

void TileLayer::update(void) { }

void TileLayer::setTileIdList(const std::vector<std::vector<int>> &pTileIdList) {
  mTileIdList = pTileIdList;
}

void TileLayer::setTileSize(int pTileSize) {
  mTileSize = pTileSize;
}

int TileLayer::getTileIdByPosition(int pXIndex, int pYIndex, int pDefault) {
  int xIndexMax = mTileIdList[0].size();
  int yIndexMax = mTileIdList.size();
  if ((pXIndex < 0) || (xIndexMax <= pXIndex) || (pYIndex < 0) || (yIndexMax <= pYIndex)) {
    return pDefault;
  }
  return mTileIdList[pYIndex][pXIndex];
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

