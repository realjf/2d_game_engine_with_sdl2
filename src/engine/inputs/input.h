#ifndef _INPUT_H_
#define _INPUT_H_

#include <SDL.h>

enum Axis { HORIZONTAL,
            VERTICAL };

class Input {
public:
    static Input *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Input(); }

    void Listen();
    bool GetKeyDown(SDL_Scancode key);

    int GetAxisKey(Axis axis);

private:
    Input();
    void KeyUp(SDL_KeyboardEvent *event);
    void KeyDown(SDL_KeyboardEvent *event);

private:
    const Uint8 *m_KeyStates;
    static Input *s_Instance;
};

#endif /* _INPUT_H_ */
