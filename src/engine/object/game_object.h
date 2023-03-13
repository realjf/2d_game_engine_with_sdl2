#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "object.h"
#include "physics/transform.h"
#include <SDL.h>
#include "math/point.h"

enum class ObjectCategory {
    OBJECT = 0,
    PLAYER,
    ENEMY
};

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
        m_Transform = new Transform(props->X, props->Y, props->Width, props->Height, props->TextureID);
        float px = props->X + (props->Width * props->Scale) / 2;
        float py = props->Y + (props->Height * props->Scale) / 2;
        m_Origin = new Point(px, py);
    }

    inline Point *GetOrigin() { return m_Origin; }
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
    float m_XScale, m_YScale;
    Point *m_Origin;
    ObjectCategory m_Category;
};

using ObjectPtr = GameObject *;
using ObjectList = std::vector<ObjectPtr>;

#endif /* _GAME_OBJECT_H_ */
