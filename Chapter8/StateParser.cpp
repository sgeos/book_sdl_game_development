#include <iostream>
#include <string>
#include <vector>
#include "Constants.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "StateParser.h"
#include "TextureManager.h"
#include "tinyxml.h"

bool StateParser::parseState(
  const char *pFilename,
  std::string pStateId,
  std::vector<GameObject *> *pObjectList,
  std::vector<std::string> *pTextureIdList
) {
  const std::string resourcePath = Constants::ResourcePath("");
  TiXmlDocument document;
  bool success = document.LoadFile(resourcePath + pFilename);
  if (false == success) {
    std::cerr << document.ErrorDesc() << std::endl;
  } else {
    TiXmlElement *root = document.RootElement();
    TiXmlElement *stateRoot = getFirstChildById(root, pStateId);
    TiXmlElement *textureRoot = getFirstChildById(stateRoot, std::string("textures"));
    parseTextures(textureRoot, pTextureIdList);
    TiXmlElement *objectRoot = getFirstChildById(stateRoot, std::string("objects"));
    parseObjects(objectRoot, pObjectList);
  }
  return success;
}

TiXmlElement *StateParser::getFirstChildById(TiXmlElement *pParent, std::string pChildId) {
  for (TiXmlElement *e = pParent->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    if (pChildId == e->Value()) {
      return e;
    }
  }
  return nullptr;
}

void StateParser::parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjectList) {
  for (TiXmlElement *e = pStateRoot->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    std::string type = e->Attribute("type");
    std::string textureId = e->Attribute("texture_id");
    int x = 0;
    e->Attribute("x", &x);
    int y = 0;
    e->Attribute("y", &y);
    int width = 0;
    e->Attribute("width", &width);
    int height = 0;
    e->Attribute("height", &height);
    double scale = 1.0;
    e->Attribute("scale", &scale);
    double rotation = 0.0;
    e->Attribute("rotation", &rotation);
    double alpha = 1.0;
    e->Attribute("alpha", &alpha);
    bool xFlip = nullptr != e->Attribute("x_flip") && 0 == std::string("true").compare(e->Attribute("x_flip"));
    bool yFlip = nullptr != e->Attribute("y_flip") && 0 == std::string("true").compare(e->Attribute("y_flip"));
    int animationRow = 0;
    e->Attribute("animation_row", &animationRow);
    int animationFrame = 0;
    e->Attribute("animation_frame", &animationFrame);
    int animationFrameCount = 1;
    e->Attribute("animation_frame_count", &animationFrameCount);
    int animationCounter = 0;
    e->Attribute("animation_counter", &animationCounter);
    int animationSpeed = 1;
    e->Attribute("animation_speed", &animationSpeed);
    int maxIntensity = 255;
    e->Attribute("max_intensity", &maxIntensity);
    int callbackId = 0;
    e->Attribute("callback_id", &callbackId);
    GameObject *gameObject = GameObjectFactory::Instance()->create(type);
    gameObject->load(
      std::unique_ptr<LoaderParams>(
        new LoaderParams(
          textureId,
          x,
          y,
          width,
          height,
          scale,
          rotation,
          alpha,
          xFlip,
          yFlip,
          animationRow,
          animationFrame,
          animationFrameCount,
          animationCounter,
          animationSpeed,
          maxIntensity,
          callbackId
        )
      )
    );
    pObjectList->push_back(gameObject);
  }
}

void StateParser::parseTextures(TiXmlElement *pStateRoot, std::vector<std::string> *pTextureIdList) {
  const std::string resourcePath = Constants::ResourcePath("");
  for (TiXmlElement *e = pStateRoot->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()) {
    std::string id = e->Attribute("id");
    std::string filename = e->Attribute("filename");
    TextureManager::Instance()->load(id, resourcePath + filename);
    pTextureIdList->push_back(id);
  }
}

