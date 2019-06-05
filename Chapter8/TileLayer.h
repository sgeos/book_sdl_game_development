#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include <vector>
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"

class TileLayer : public Layer {
  public:
    TileLayer(int pTileSize, const std::vector<struct Tileset> &pTilesetList);
    virtual void render(void);
    virtual void update(void);
    void setTileIds(const std::vector<std::vector<int>> &pTileIdList);
    void setTileSize(int pTileSize);
    void setMapWidth(int pMapWidth) { mMapWidth = pMapWidth; }
    int getTileIdByPosition(int pXIndex, int pYIndex);
    Tileset getTilesetById(int pTileId);

  private:
    int mColumnCount;
    int mRowCount;
    int mTileSize;
    int mMapWidth;
    Vector2D mPosition;
    Vector2D mVelocity;
    const std::vector<Tileset> &mTilesetList;
    std::vector<std::vector<int>> mTileIdList;
};

#endif // TILE_LAYER_H

