#include <vector>
#include "Bullet.h"
#include "BulletHandler.h"
#include "Game.h"

BulletHandler *BulletHandler::sInstance;

BulletHandler::BulletHandler(void) { }

BulletHandler::~BulletHandler(void) { cleanup(); }

void BulletHandler::addPlayerBullet(
  std::string pTextureId,
  int pX,
  int pY,
  int pWidth,
  int pHeight,
  int pAnimationFrameCount,
  Vector2D pHeading
) {
  PlayerBullet *bullet = new PlayerBullet();
  bullet->load(
    std::unique_ptr<LoaderParams>(
      new LoaderParams(
        pTextureId,
        pX,
        pY,
        pWidth,
        pHeight,
        1.0,    // scale
        0.0,    // rotation
        1.0,    // alpha
        false,  // xFlip
        false,  // yFlip
        0,      // animationRow
        0,      // animationFrame
        pAnimationFrameCount,
        0,      // animationCounter
        1       // animationSpeed
      )
    )
  );
  bullet->setHeading(pHeading);
  mPlayerBulletList.push_back(bullet);
}

void BulletHandler::addEnemyBullet(
  std::string pTextureId,
  int pX,
  int pY,
  int pWidth,
  int pHeight,
  int pAnimationFrameCount,
  Vector2D pHeading
) {
  EnemyBullet *bullet = new EnemyBullet();
  bullet->load(
    std::unique_ptr<LoaderParams>(
      new LoaderParams(
        pTextureId,
        pX,
        pY,
        pWidth,
        pHeight,
        1.0,    // scale
        0.0,    // rotation
        1.0,    // alpha
        false,  // xFlip
        false,  // yFlip
        0,      // animationRow
        0,      // animationFrame
        pAnimationFrameCount,
        0,      // animationCounter
        1       // animationSpeed
      )
    )
  );
  bullet->setHeading(pHeading);
  mEnemyBulletList.push_back(bullet);
}

void BulletHandler::draw(void) {
  for (int i = 0; i < mPlayerBulletList.size(); i++) {
    mPlayerBulletList[i]->draw();
  }
  for (int i = 0; i < mEnemyBulletList.size(); i++) {
    mEnemyBulletList[i]->draw();
  }
}

void BulletHandler::update(void) {
  for (std::vector<PlayerBullet *>::iterator item = mPlayerBulletList.begin(); mPlayerBulletList.end() != item; item++) {
    if (
      (*item)->getPosition().getX() < 0 || Game::Instance()->getWidth() < (*item)->getPosition().getX() ||
      (*item)->getPosition().getY() < 0 || Game::Instance()->getHeight() < (*item)->getPosition().getY() ||
      (*item)->dead()
    ) {
      delete *item;
      item = mPlayerBulletList.erase(item);
    } else {
      (*item)->update();
    }
  }
  for (std::vector<EnemyBullet *>::iterator item = mEnemyBulletList.begin(); mEnemyBulletList.end() != item; item++) {
    if (
      (*item)->getPosition().getX() < 0 || Game::Instance()->getWidth() < (*item)->getPosition().getX() ||
      (*item)->getPosition().getY() < 0 || Game::Instance()->getHeight() < (*item)->getPosition().getY() ||
      (*item)->dead()
    ) {
      delete *item;
      item = mEnemyBulletList.erase(item);
    } else {
      (*item)->update();
    }
  }
}

void BulletHandler::cleanup(void) {
  mPlayerBulletList.clear();
  mEnemyBulletList.clear();
}

