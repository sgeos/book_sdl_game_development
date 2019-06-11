#include <SDL2/SDL.h>
#include <vector>
#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "TileLayer.h"

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject *> &pObjectList) {
  for (int i = 0; i < pObjectList.size(); i++) {
    GameObject *object = pObjectList[i];
    if (std::string("Enemy") != object->type() || !object->updating()) {
      continue;
    }
    testCollision(pPlayer, object);
  }
}

SDL_Rect *CollisionManager::getGameObjectRectangle(GameObject *pGameObject) {
  SDL_Rect *gameObjectRectangle = new SDL_Rect();
  gameObjectRectangle->x = pGameObject->getPosition().getX();
  gameObjectRectangle->y = pGameObject->getPosition().getY();
  gameObjectRectangle->w = pGameObject->getWidth();
  gameObjectRectangle->h = pGameObject->getHeight();
  return gameObjectRectangle;
}

void CollisionManager::testCollision(GameObject *pGameObjectA, GameObject *pGameObjectB) {
  SDL_Rect *rectangleA = getGameObjectRectangle(pGameObjectA);
  SDL_Rect *rectangleB = getGameObjectRectangle(pGameObjectB);
  if (RectangleRectangle(rectangleA, rectangleB)) {
    if (!pGameObjectA->dying() && !pGameObjectB->dying()) {
      pGameObjectA->collision();
      pGameObjectB->collision();
    }
  }
  delete rectangleB;
  delete rectangleA;
}

