#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include "GameObject.h"
#include "tinyxml.h"

class StateParser {
  public:
    bool parseState(
      const char *pFilename,
      std::string pStateId,
      std::vector<GameObject *> *pObjectList,
      std::vector<std::string> *pTextureIdList
    );

  private:
    TiXmlElement *getFirstChildById(TiXmlElement *pParent, std::string pChildId);
    void parseObjects(TiXmlElement *pStateRoot, std::vector<GameObject *> *pObjectList);
    void parseTextures(TiXmlElement *pStateRoot, std::vector<std::string> *pTextureIdList);
};

#endif // STATE_PARSER_H

