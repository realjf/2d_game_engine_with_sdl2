#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "math/vector2D.h"

class Transform {
public:
    float X, Y;
    float Rotation;
    int Width, Height;
    Vector2D *Origin;
    float ScrollRatio;
    float ScaleX, ScaleY;
    SDL_RendererFlip Flip;
    std::string TextureID;

public:
    Transform(float x = 0.0f, float y = 0.0f, int width = 0.0f, int height = 0.0f,
              std::string textureID = "", float scaleX = 1.0f, float scaleY = 1.0f,
              float rotation = 0.0f, float scrollRatio = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        ScaleX = scaleX;
        ScaleY = scaleY;
        Rotation = rotation;
        TextureID = textureID;
        ScrollRatio = scrollRatio;
        Origin = new Vector2D((X + Width), (Y + Height));
    }

    void Log(std::string msg = "") {
        std::cout << msg << "(X,Y) = (" << X << "," << Y << ")" << std::endl;
    }

    inline void TranslateX(float x) { X += x; }
    inline void TranslateY(float y) { Y += y; }
    inline void Translate(Vector2D v) {
        X += v.X;
        Y += v.Y;
    }
};

#endif /* _TRANSFORM_H_ */
