#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "math/vector2D.h"

class Transform {
public:
    float X, Y;

public:
    Transform(float x = 0.0f, float y = 0.0f) : X(x), Y(y) {}

    void Log(std::string msg = "") {
        std::cout << msg << "(X,Y) = (" << X << "," << Y << ")" << std::endl;
    }

private:
    inline void TranslateX(float x) { X += x; }
    inline void TranslateY(float y) { Y += y; }
    inline void Translate(Vector2D v) {
        X += v.X;
        Y += v.Y;
    }
};

#endif /* _TRANSFORM_H_ */
