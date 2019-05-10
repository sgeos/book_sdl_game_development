#include <vector>
#include "base64.h"
#include "Constants.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "Level.h"
#include "LevelParser.h"
#include "ObjectLayer.h"
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
    if (std::string("properties") == e->Value()) {
      parseTextureList(e);
    }
  }
  for (TiXmlElement *e = root->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    if (std::string("objectgroup") == e->Value()) {
      parseObjectLayer(e, level->getLayerList());
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
  std::cout << "Adding tileset " << imageElement->Attribute("source") << " with ID " << pTilesetRoot->Attribute("name") << std::endl;
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

void LevelParser::parseTextureList(TiXmlElement *pTextureRoot) {
  const std::string resourcePath = Constants::ResourcePath("");
  for (TiXmlElement *e = pTextureRoot->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    if (std::string("property") == e->Value()) {
      std::cout << "Adding texture " << e->Attribute("value") << " with ID " << e->Attribute("name") << std::endl;
      TextureManager::Instance()->load(e->Attribute("name"), resourcePath + e->Attribute("value"));
    }
  }
}

void LevelParser::parseObjectLayer(TiXmlElement *pObjectElement, std::vector<Layer *> *pLayerList) {
  ObjectLayer* objectLayer = new ObjectLayer();
  for (TiXmlElement *e = pObjectElement->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    std::cout << e->Value() << std::endl;
    if (std::string("object") == e->Value()) {
      std::string type = e->Attribute("type");
      GameObject *gameObject = GameObjectFactory::Instance()->create(type);
      if (nullptr == gameObject) {
        std::cout << "Failed to create game object: " << e->Attribute("type") << std::endl;
      } else {
        std::cout << "Creating game object: " << e->Attribute("type") << std::endl;
        std::string textureId;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        double scale = 1.0;
        double rotation = 0.0;
        bool xFlip = false;
        bool yFlip = false;
        int animationCounter = 0;
        int animationFrame = 0;
        int animationRow = 0;
        int animationSpeed = 1;
        int animationFrames = 0;
        int maxIntensity = 255;
        int callbackId = 0;
        e->Attribute("x", &x);
        e->Attribute("y", &y);
        for (TiXmlElement* properties = e->FirstChildElement(); nullptr != properties; properties = properties->NextSiblingElement()) {
          if (std::string("properties") == properties->Value()) {
            for (TiXmlElement* property = properties->FirstChildElement(); nullptr != property; property = property->NextSiblingElement()) {
              if (std::string("texture_id") == property->Attribute("name")) {
                textureId = property->Attribute("value");
              } else if (std::string("width") == property->Attribute("name")) {
                property->Attribute("value", &width);
              } else if (std::string("height") == property->Attribute("name")) {
                property->Attribute("value", &height);
              } else if (std::string("scale") == property->Attribute("name")) {
                property->Attribute("value", &scale);
              } else if (std::string("rotation") == property->Attribute("name")) {
                property->Attribute("value", &rotation);
              } else if (std::string("x_flip") == property->Attribute("name") && nullptr != property->Attribute("value")) {
                xFlip = 0 == std::string("true").compare(property->Attribute("value"));
              } else if (std::string("y_flip") == property->Attribute("name") && nullptr != property->Attribute("value")) {
                yFlip = 0 == std::string("true").compare(property->Attribute("value"));
              } else if (std::string("animation_counter") == property->Attribute("name")) {
                property->Attribute("value", &animationCounter);
              } else if (std::string("animation_frame") == property->Attribute("name")) {
                property->Attribute("value", &animationFrame);
              } else if (std::string("animation_row") == property->Attribute("name")) {
                property->Attribute("value", &animationRow);
              } else if (std::string("animation_speed") == property->Attribute("name")) {
                property->Attribute("value", &animationSpeed);
              } else if (std::string("animation_frames") == property->Attribute("name")) {
                property->Attribute("value", &animationFrames);
              } else if (std::string("max_intensity") == property->Attribute("name")) {
                property->Attribute("value", &maxIntensity);
              } else if (std::string("callback_id") == property->Attribute("name")) {
                property->Attribute("value", &callbackId);
              }
            }
          }
        }
        gameObject->load(
          new LoaderParams(
            textureId,
            x,
            y,
            width,
            height,
            scale,
            rotation,
            xFlip,
            yFlip,
            animationCounter,
            animationFrame,
            animationRow,
            animationSpeed,
            animationFrames,
            maxIntensity,
            callbackId
          )
        );
        objectLayer->getGameObjectList()->push_back(gameObject);
      }
    }
  }
  pLayerList->push_back(objectLayer);
}

