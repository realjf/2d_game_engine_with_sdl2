#include "camera.h"

Camera *Camera::s_Instance = nullptr;

void Camera::Update(float dt) {
    if (m_Target != nullptr) {
        m_ViewPort.x = m_Target->X - SCREEN_WIDTH / 2;
        m_ViewPort.y = m_Target->Y - SCREEN_HEIGHT / 2;

        if (m_ViewPort.x < 0) {
            m_ViewPort.x = 0;
        }
        if (m_ViewPort.y < 0) {
            m_ViewPort.y = 0;
        }

        if (m_ViewPort.x > (m_SceneWidth - m_ViewPort.w)) {
            m_ViewPort.x = (m_SceneWidth - m_ViewPort.w);
        }

        if (m_ViewPort.y > (m_SceneHeight - m_ViewPort.h)) {
            m_ViewPort.y = (m_SceneHeight - m_ViewPort.h);
        }

        // std::cout << "ViewBox: " << m_Target->X << "," << m_Target->Y << "," << m_ViewPort.x << "," << m_ViewPort.y << "," << m_ViewPort.w << "," << m_ViewPort.h << std::endl;
        m_CurrentPosition = Vector2D(m_ViewPort.x, m_ViewPort.y);
    }
}

bool Camera::GetInsectionWithViewPort(const SDL_Rect *rect)
{

}
