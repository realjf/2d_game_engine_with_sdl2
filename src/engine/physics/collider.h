#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include <SDL.h>
#include "collision/collision_manager.h"
#include "camera/camera.h"
#include "engine.h"

class Collider {
public:
    inline SDL_Rect Get() { return m_Box; }
    inline void SetBuffer(int x, int y, int w, int h) {
        m_Buffer = {x, y, w, h};
    }

    void Set(int x, int y, int w, int h) {
        m_Box = {
            x - m_Buffer.x,
            y - m_Buffer.y,
            w - m_Buffer.w,
            h - m_Buffer.h};
    }

    bool CollideWithMap() {
        return CollisionManager::GetInstance()->MapCollision(m_Box);
    }

    void Draw() {
        Vector2D cam = Camera::GetInstance()->GetPosition();
        SDL_Rect box = {
            (int)(m_Box.x - cam.X),
            (int)(m_Box.y - cam.Y),
            m_Box.w,
            m_Box.h};
        SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    }

private:
    SDL_Rect m_Box;
    SDL_Rect m_Buffer;
};

#endif /* _COLLIDER_H_ */
