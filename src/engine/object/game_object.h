#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <vector>
#include "object.h"
#include "physics/transform.h"
#include <SDL.h>
#include "math/point.h"

enum class ObjectCategory {
    OBJECT = 0,
    PLAYER,
    ENEMY
};

class GameObject : public Object {

public:
    GameObject(Transform *tf) : m_Transform(tf) {
    }

    virtual ~GameObject() {
    }

    virtual void Draw() = 0;
    virtual void Update(float dt) = 0;
    virtual void Clean() = 0;

    inline Transform *GetTransform() { return m_Transform; }
    inline ObjectCategory GetCategory() { return m_Category; }
    inline Vector2D *GetOrigin() { return m_Transform->Origin; }

protected:
    Transform *m_Transform;
    ObjectCategory m_Category;
};

using ObjectPtr = GameObject *;
using ObjectList = std::vector<ObjectPtr>;

#endif /* _GAME_OBJECT_H_ */
