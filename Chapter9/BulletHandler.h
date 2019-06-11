#ifndef BULLET_HANDLER_H
#define BULLET_HANDLER_H

#include <vector>
#include "Bullet.h"

class BulletHandler {
  public:
    static BulletHandler *Instance(void) {
      if (nullptr == sInstance) {
        sInstance = new BulletHandler();
      }
      return sInstance;
    }
    void addPlayerBullet(
      std::string pTextureId,
      int pX,
      int pY,
      int pWidth,
      int pHeight,
      int pAnimationFrameCount,
      Vector2D pHeading
    );
    void addEnemyBullet(
      std::string pTextureId,
      int pX,
      int pY,
      int pWidth,
      int pHeight,
      int pAnimationFrameCount,
      Vector2D pHeading
    );
    void draw(void);
    void update(void);
    void cleanup(void);
    const std::vector<PlayerBullet *> getPlayerBulletList(void) { return mPlayerBulletList; }
    const std::vector<EnemyBullet *> getEnemyBulletList(void) { return mEnemyBulletList; }

  private:
    static BulletHandler *sInstance;
    std::vector<PlayerBullet *> mPlayerBulletList;
    std::vector<EnemyBullet *> mEnemyBulletList;

    BulletHandler(void);
    ~BulletHandler(void);
    BulletHandler(const BulletHandler &);
    BulletHandler& operator=(const BulletHandler &);
};

#endif // BULLET_HANDLER_H

