#include "input.h"
#include "engine.h"

Input *Input::s_Instance = nullptr;

Input::Input() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            Engine::GetInstance()->Quit();
            break;
        case SDL_KEYDOWN:
            KeyDown(&event.key);
            break;
        case SDL_KEYUP:
            KeyUp(&event.key);
            break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key) {
    if (m_KeyStates[key] == 1)
        return true;

    return false;
}

void Input::KeyUp(SDL_KeyboardEvent *event) {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(SDL_KeyboardEvent *event) {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}
