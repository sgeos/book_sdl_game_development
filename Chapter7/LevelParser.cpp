#include <vector>
#include "base64.h"
#include "Constants.h"
#include "Game.h"
#include "Level.h"
#include "LevelParser.h"
#include "TextureManager.h"
#include "TileLayer.h"
#include "tinyxml.h"
#include "zlib.h"

Level *LevelParser::parseLevel(const char *pFilename) {
  const std::string resourcePath = Constants::ResourcePath("");
  TiXmlDocument document;
  document.LoadFile(resourcePath + pFilename);
  TiXmlElement *root = document.RootElement();
  root->Attribute("tilewidth", &mTileSize);
  root->Attribute("width", &mWidth);
  root->Attribute("height", &mHeight);
  Level *level = new Level();
  for (TiXmlElement *e = root->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    if (std::string("tileset") == e->Value()) {
      parseTilesetList(e, level->getTilesetList());
    }
  }
  for (TiXmlElement *e = root->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    if (std::string("layer") == e->Value()) {
      parseTileLayer(e, level->getLayerList(), level->getTilesetList());
    }
  }
  return level;
}

void LevelParser::parseTilesetList(TiXmlElement *pTilesetRoot, std::vector<Tileset> *pTilesetList) {
  const std::string resourcePath = Constants::ResourcePath("");
  TiXmlElement *imageElement = pTilesetRoot->FirstChildElement();
  TextureManager::Instance()->load(pTilesetRoot->Attribute("name"), resourcePath + imageElement->Attribute("source"));
  Tileset tileset;
  imageElement->Attribute("width", &tileset.width);
  imageElement->Attribute("height", &tileset.height);
  pTilesetRoot->Attribute("firstgid", &tileset.firstGridId);
  pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
  pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
  pTilesetRoot->Attribute("spacing", &tileset.spacing);
  pTilesetRoot->Attribute("margin", &tileset.margin);
  tileset.name = pTilesetRoot->Attribute("name");
  tileset.columnCount = tileset.width / (tileset.tileWidth + tileset.spacing);
  pTilesetList->push_back(tileset);
}

void LevelParser::parseTileLayer(TiXmlElement *pTileElement, std::vector<Layer *> *pLayerList, const std::vector<Tileset> *pTileSetList) {
  TileLayer *tileLayer = new TileLayer(mTileSize, *pTileSetList);
  std::vector<std::vector<int>> tileData;
  std::string decodedIds;
  TiXmlElement *dataNode;
  for (TiXmlElement *e = pTileElement->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    if (std::string("data") == e->Value()) {
      dataNode = e;
    }
  }
  for (TiXmlNode *e = dataNode->FirstChild(); nullptr != e; e = e->NextSibling()) {
    TiXmlText *text = e->ToText();
    std::string t = text->Value();
    decodedIds = base64_decode(t);
  }
  uLongf gidCount = mWidth * mHeight * sizeof(int);
  std::vector<unsigned> gidList(gidCount);
  uncompress((Bytef *)&gidList[0], &gidCount, (const Bytef *)decodedIds.c_str(), decodedIds.size());
  std::vector<int> layerRow(mWidth);
  for (int j = 0; j < mHeight; j++) {
    tileData.push_back(layerRow);
  }
  for (int row = 0; row < mHeight; row++) {
    for (int column = 0; column < mWidth; column++) {
      tileData[row][column] = gidList[row * mWidth + column];
    }
  }
  tileLayer->setTileIds(tileData);
  pLayerList->push_back(tileLayer);
}

