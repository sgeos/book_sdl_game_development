#include <SDL2/SDL.h>
#include <vector>
#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"
#include "TileLayer.h"

void CollisionManager::checkPlayerEnemyBulletCollision(Player *pPlayer) {
  for (int i = 0; i < BulletHandler::Instance()->getEnemyBulletList().size(); i++) {
    EnemyBullet *enemyBullet = BulletHandler::Instance()->getEnemyBulletList()[i];
    testCollision(pPlayer, enemyBullet);
  }
}

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject *> &pObjectList) {
  for (int i = 0; i < pObjectList.size(); i++) {
    GameObject *object = pObjectList[i];
    if (std::string("Enemy") != object->type() || !object->updating()) {
      continue;
    }
    testCollision(pPlayer, object);
  }
}

void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject *> &pObjectList) {
  for (int i = 0; i < pObjectList.size(); i++) {
    GameObject *object = pObjectList[i];
    if (std::string("Enemy") != object->type() || !object->updating()) {
      continue;
    }
    for (int j = 0; j < BulletHandler::Instance()->getPlayerBulletList().size(); j++) {
      PlayerBullet *playerBullet = BulletHandler::Instance()->getPlayerBulletList()[j];
      testCollision(object, playerBullet);
    }
  }
}

void CollisionManager::checkPlayerTileCollision(Player* pPlayer, const std::vector<TileLayer *> &pCollisionLayerList) {
  for (
    std::vector<TileLayer*>::const_iterator iterator = pCollisionLayerList.begin();
    pCollisionLayerList.end() != iterator;
    ++iterator
  ) {
    TileLayer* tileLayer = (*iterator);
    std::vector<std::vector<int>> tiles = tileLayer->getTileIdList();
    Vector2D layerPosition = tileLayer->getPosition();
    int x, y, tileColumn, tileRow, tileId;
    x = layerPosition.getX() / tileLayer->getTileSize();
    y = layerPosition.getY() / tileLayer->getTileSize();
    if (0 <= pPlayer->getVelocity().getX() || 0 <= pPlayer->getVelocity().getY()) {
      tileColumn = ((pPlayer->getPosition().getX() + pPlayer->getWidth()) / tileLayer->getTileSize());
      tileRow = ((pPlayer->getPosition().getY() + pPlayer->getHeight()) / tileLayer->getTileSize());
      tileId = tiles[tileRow + y][tileColumn + x];
    } else if (pPlayer->getVelocity().getX() < 0 || pPlayer->getVelocity().getY() < 0) {
      tileColumn = pPlayer->getPosition().getX() / tileLayer->getTileSize();
      tileRow = pPlayer->getPosition().getY() / tileLayer->getTileSize();
      tileId = tiles[tileRow + y][tileColumn + x];
    } else {
      tileId = 0;
    }
    if (0 != tileId) {
      pPlayer->collision();
    }
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

