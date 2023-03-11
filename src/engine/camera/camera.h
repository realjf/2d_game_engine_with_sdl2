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

private:
    Camera() {
        m_ViewBox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    }

    Point *m_Target;
    Vector2D m_Position;
    SDL_Rect m_ViewBox;

    static Camera *s_Instance;
};

#endif /* _CAMERA_H_ */
