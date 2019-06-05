#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Layer.h"
#include "Player.h"
#include "TileLayer.h"

struct Tileset {
  int firstGridId;
  int tileWidth;
  int tileHeight;
  int spacing;
  int margin;
  int width;
  int height;
  int columnCount;
  std::string name;
};

class Level {
  public:
    ~Level(void);
    void render(void);
    void update(void);
    std::vector<Tileset> *getTilesetList(void);
    std::vector<Layer *> *getLayerList(void);
    std::vector<TileLayer *> *getCollisionLayerList(void) { return &mCollisionLayerList; }
    void setPlayer(Player *pPlayer) { mPlayer = pPlayer; }
    Player *getPlayer(void) { return mPlayer; }

  private:
    friend class LevelParser;
    Level(void);
    Player *mPlayer;
    std::vector<Tileset> mTilesetList;
    std::vector<Layer *> mLayerList;
    std::vector<TileLayer *> mCollisionLayerList;
};

#endif // LEVEL_H

