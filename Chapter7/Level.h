#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "Layer.h"

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
    Level(void);
    ~Level(void);
    void render(void);
    void update(void);
    std::vector<Tileset> *getTilesetList(void);
    std::vector<Layer *> *getLayerList(void);

  private:
    std::vector<Tileset> mTilesetList;
    std::vector<Layer *> mLayerList;
};

#endif // LEVEL_H

