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

    inline SDL_Rect GetViewBox() { return m_ViewBox; }
    inline Vector2D GetPosition() { return m_Position; }
    inline void SetTarget(Point *target) { m_Target = target; }
    inline void SetSceneLimit(int width, int height) {
        m_SceneWidth = width;
        m_SceneHeight = height;
    }
    inline int GetSceneWidth() { return m_SceneWidth; }
    inline int GetSceneHeight() { return m_SceneHeight; }

    inline void MoveX(float x) { m_Position.X = x; }
    inline void MoveY(float y) { m_Position.Y = y; }

private:
    Camera() {
        m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    }

    Point *m_Target;
    Vector2D m_Position;
    SDL_Rect m_ViewBox;
    int m_SceneWidth, m_SceneHeight;

    static Camera *s_Instance;
};

#endif /* _CAMERA_H_ */
