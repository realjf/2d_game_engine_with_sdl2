#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SDL.h>
#include "math/point.h"
#include "math/vector2D.h"
#include "engine.h"

class Camera {
public:
    void Update(float dt);
    inline static Camera *GetInstance() { return s_Instance = (s_Instance == nullptr) ? new Camera() : s_Instance; }

    inline SDL_Rect GetViewBox() { return m_ViewPort; }
    inline Vector2D GetPosition() { return m_CurrentPosition; }
    inline void SetTarget(Point *target) { m_Target = target; }
    inline void SetSceneLimit(int width, int height) {
        m_SceneWidth = width;
        m_SceneHeight = height;
    }
    inline int GetSceneWidth() { return m_SceneWidth; }
    inline int GetSceneHeight() { return m_SceneHeight; }

    inline void MoveX(float x) { m_CurrentPosition.X = x; }
    inline void MoveY(float y) { m_CurrentPosition.Y = y; }

    const Vector2D SyncObject(Transform tf) {
        const float targetX = (tf.X - m_CurrentPosition.X * tf.SyncRatio);
        const float targetY = (tf.Y - m_CurrentPosition.Y * tf.SyncRatio);
        return Vector2D(targetX, targetY);
    }

    void Draw() {
        SDL_Renderer *rdr = Engine::GetInstance()->GetRenderer();
        SDL_SetRenderDrawColor(rdr, 0xFF, 0x50, 0x50, 0xFF);
        SDL_RenderDrawRect(rdr, &m_ViewPort);
    }

    bool GetInsectionWithViewPort(const SDL_Rect *rect);

private:
    Camera() {
        m_ViewPort = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    }

    Point *m_Target;
    Vector2D m_CurrentPosition;
    SDL_Rect m_ViewPort;
    int m_SceneWidth, m_SceneHeight;

    static Camera *s_Instance;
};

#endif /* _CAMERA_H_ */
