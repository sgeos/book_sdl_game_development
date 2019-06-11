#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SDL2/SDL.h>
#include <vector>

class GameObject;
class Player;
class TileLayer;

class CollisionManager {
  public:
    void checkPlayerEnemyBulletCollision(Player *pPlayer);
    void checkPlayerEnemyCollision(Player *pPlayer, const std::vector<GameObject *> &pObjectList);
    void checkEnemyPlayerBulletCollision(const std::vector<GameObject *> &pObjectList);
    void checkPlayerTileCollision(Player *pPlayer, const std::vector<TileLayer *> &pCollisionLayerList);

  private:
    SDL_Rect *getGameObjectRectangle(GameObject *pGameObject);
    void testCollision(GameObject *pGameObjectA, GameObject *pGameObjectB);
};

#endif // COLLISION_MANAGER_H

