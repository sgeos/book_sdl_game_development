#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <SDL2/SDL.h>
#include <vector>

class GameObject;
class Player;
class TileLayer;

class CollisionManager {
  public:
    void checkPlayerEnemyCollision(Player *pPlayer, const std::vector<GameObject *> &pObjectList);

  private:
    SDL_Rect *getGameObjectRectangle(GameObject *pGameObject);
    void testCollision(GameObject *pGameObjectA, GameObject *pGameObjectB);
};

#endif // COLLISION_MANAGER_H

