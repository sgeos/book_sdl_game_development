#ifndef TILE_LAYER_H
#define TILE_LAYER_H

#include <vector>
#include "Layer.h"
#include "Level.h"
#include "Vector2D.h"

class TileLayer : public Layer {
  public:
    TileLayer(int pTileSize, int pMapWidth, int pMapHeight, const std::vector<struct Tileset> &pTilesetList);
    virtual ~TileLayer(void) { }
    virtual void render(void);
    virtual void update(void);
    void setTileIdList(const std::vector<std::vector<int>> &pTileIdList);
    void setTileSize(int pTileSize);
    int getMapWidth(void) { return mMapWidth; }
    void setMapWidth(int pMapWidth) { mMapWidth = pMapWidth; }
    int getTileIdByPosition(int pXIndex, int pYIndex, int pDefault);
    Tileset getTilesetById(int pTileId);
    int getTileSize(void) { return mTileSize; }
    const std::vector<std::vector<int>>& getTileIdList() { return mTileIdList; }
    const Vector2D getPosition(void) { return mPosition; }
    void setPosition(Vector2D pPosition) { mPosition = pPosition; }

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

