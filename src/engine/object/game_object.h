#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "object.h"
#include "physics/transform.h"
#include <SDL.h>

struct Properties {
public:
    Properties(std::string textureID, int x, int y, int width, int height, float scale, SDL_RendererFlip flip = SDL_FLIP_NONE) {
        X = x;
        Y = y;
        Width = width;
        Height = height;
        TextureID = textureID;
        Flip = flip;
        Scale = scale;
    }

public:
    std::string TextureID;
    int Width, Height;
    float X, Y;
    SDL_RendererFlip Flip;
    float Scale;
};

class GameObject : public Object {

public:
    GameObject(Properties *props) : m_Width(props->Width), m_Height(props->Height), m_TextureID(props->TextureID), m_Flip(props->Flip), m_Scale(props->Scale) {
        m_Transform = new Transform(props->X, props->Y);
    }
    virtual ~GameObject() {}

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

protected:
    Transform *m_Transform;
    int m_Width, m_Height;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
    float m_Scale;
};

#endif /* _GAME_OBJECT_H_ */
