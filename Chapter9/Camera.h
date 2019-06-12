#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2D.h"

class Camera {
  public:
    static Camera *Instance(void) {
      if (nullptr == sInstance) {
        sInstance = new Camera();
      }
      return sInstance;
    }
    void update(Vector2D pVelocity);
    void setTarget(Vector2D* pTarget) { mTarget = pTarget; }
    void setPosition(const Vector2D &pPosition) { mPosition = pPosition; }
    const Vector2D getPosition(void) const;

  private:
    Camera(void);
    ~Camera(void);

    static Camera *sInstance;
    Vector2D mPosition;
    Vector2D *mTarget;
};

#endif // CAMERA_H

