#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include <vector>
#include "Level.h"
#include "tinyxml.h"

class LevelParser {
  public:
    Level *parseLevel(const char *pFilename);

  private:
    void parseTilesetList(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTileSetList);
    void parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayerList, const std::vector<Tileset> *pTilesetList);
    void parseTextureList(TiXmlElement *pTextureRoot);
    void parseObjectLayer(TiXmlElement *pObjectElement, std::vector<Layer *> *pLayerList);
    int mTileSize;
    int mWidth;
    int mHeight;
};

#endif // LEVEL_PARSER_H

