#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <math.h>

class Vector2D {
  public:
    Vector2D(float pX, float pY) : mX(pX), mY(pY) { }
    float getX(void) const { return mX; }
    float getY(void) const { return mY; }
    void setX(float pX) { mX = pX; }
    void setY(float pY) { mY = pY; }
    float length(void) const { return sqrt(mX*mX + mY*mY); }
    void normalize(void) {
      float vectorLength = length();
      if (0 < vectorLength) {
        (*this) /= vectorLength;
      }
    }
    Vector2D operator+(const Vector2D &pVector) const {
      return Vector2D(mX + pVector.mX, mY + pVector.mY);
    }
    friend Vector2D &operator+=(Vector2D &pVectorA, const Vector2D &pVectorB) {
      pVectorA.mX += pVectorB.mX;
      pVectorA.mY += pVectorB.mY;
      return pVectorA;
    }
    Vector2D operator-(const Vector2D &pVector) const {
      return Vector2D(mX - pVector.mX, mY - pVector.mY);
    }
    friend Vector2D &operator-=(Vector2D &pVectorA, const Vector2D &pVectorB) {
      pVectorA.mX -= pVectorB.mX;
      pVectorA.mY -= pVectorB.mY;
      return pVectorA;
    }
    Vector2D operator*(float pScalar) const {
      return Vector2D(mX * pScalar, mY * pScalar);
    }
    Vector2D &operator*=(float pScalar) {
      mX *= pScalar;
      mY *= pScalar;
      return *this;
    }
    Vector2D operator/(float pScalar) const {
      return Vector2D(mX / pScalar, mY / pScalar);
    }
    Vector2D &operator/=(float pScalar) {
      mX /= pScalar;
      mY /= pScalar;
      return *this;
    }

  private:
    float mX, mY;
};

#endif // VECTOR_2D_H

