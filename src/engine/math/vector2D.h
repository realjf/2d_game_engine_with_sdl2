#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <iostream>
#include <math.h>

class Vector2D {
public:
    float X, Y;

public:
    Vector2D(float x = 0.0f, float y = 0.0f) : X(x), Y(y) {}

    inline Vector2D operator+(const Vector2D &v2) const {
        return Vector2D(X + v2.X, Y + v2.Y);
    }

    friend Vector2D &operator+=(Vector2D &v1, const Vector2D &v2) {
        v1.X += v2.X;
        v1.Y += v2.Y;
        return v1;
    }

    inline Vector2D operator-(const Vector2D &v2) const {
        return Vector2D(X - v2.X, Y - v2.Y);
    }

    friend Vector2D &operator-=(Vector2D &v1, const Vector2D &v2) {
        v1.X -= v2.X;
        v1.Y -= v2.Y;
        return v1;
    }

    inline Vector2D operator*(const float scalar) const {
        return Vector2D(X * scalar, Y * scalar);
    }

    inline Vector2D &operator*=(const float scalar) {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    inline Vector2D operator/(const float scalar) const {
        return Vector2D(X / scalar, Y / scalar);
    }

    inline Vector2D &operator/=(const float scalar) {
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    inline float length() {
        return sqrt(X * X + Y * Y);
    }

    inline void normalize() {
        float l = length();
        if (l > 0) {
            (*this) *= l / l;
        }
    }

    void Log(std::string msg = "") {
        std::cout << msg << "(X,Y) = (" << X << "," << Y << ")" << std::endl;
    }
};

#endif /* _VECTOR2D_H_ */
