#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL.h>

enum Axis { HORIZONTAL,
            VERTICAL };

enum Dir {
    NONE = 0,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_UP,
    DIR_DOWN
};

enum MouseButton {
    LEFT,
    MIDDLE,
    RIGHT
};

class Input {
public:
    static Input *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }

    void Listen();
    bool GetKeyDown(SDL_Scancode key);
    Dir GetDirectionKey();

    int GetAxisKey(Axis axis);
    inline bool MouseButtonDown(MouseButton button) { return m_MouseButtonStates[button]; }
    inline Vector2D GetMousePosition() { return m_MousePosition; }
    inline Vector2D GetMouseLastPosition() { return m_MouseLastPosition; }

private:
    Input();
    void KeyUp(SDL_KeyboardEvent *event);
    void KeyDown(SDL_KeyboardEvent *event);

    void MouseMotion(SDL_Event event);
    void MouseButtonUp(SDL_Event event);
    void MouseButtonDown(SDL_Event event);

private:
    const Uint8 *m_KeyStates;
    Vector2D m_MousePosition;
    Vector2D m_MouseLastPosition;
    std::vector<bool> m_MouseButtonStates;
    static Input *s_Instance;
};

#endif /* _INPUT_H_ */
