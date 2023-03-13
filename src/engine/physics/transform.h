#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <SDL.h>
#include "math/vector2D.h"

class Transform {
public:
    float X, Y;
    int Width, Height;
    std::string TextureID;
    float ScaleX, ScaleY;
    float Angle;
    SDL_RendererFlip Flip;
    float SyncRatio;
    Vector2D *Origin;

public:
    Transform() {}
    Transform(Transform *tf) {
        X = tf->X;
        Y = tf->Y;
        Flip = tf->Flip;
        Width = tf->Width;
        Height = tf->Height;
        ScaleX = tf->ScaleX;
        ScaleY = tf->ScaleY;
        Angle = tf->Angle;
        TextureID = tf->TextureID;
        SyncRatio = tf->SyncRatio;
        Origin = new Vector2D((X + Width * ScaleX / 2), (Y + Height * ScaleY / 2));
    }

    Transform(float x, float y, int width, int height, std::string textureID, float scaleX = 1.0f, float scaleY = 1.0f, float angle = 0.0f, float syncRatio = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        Flip = flip;
        Width = width;
        Height = height;
        ScaleX = scaleX;
        ScaleY = scaleY;
        Angle = angle;
        TextureID = textureID;
        SyncRatio = syncRatio;
        Origin = new Vector2D((X + Width * ScaleX / 2), (Y + Height * ScaleY / 2));
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
    inline void SyncOrigin() {
        Origin->X = X + Width * ScaleX / 2;
        Origin->Y = Y + Height * ScaleY / 2;
    }
};

#endif /* _TRANSFORM_H_ */
