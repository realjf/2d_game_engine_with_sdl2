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

int Input::GetAxisKey(Axis axis) {
    switch (axis) {
    case HORIZONTAL:
        if (GetKeyDown(SDL_SCANCODE_D) || GetKeyDown(SDL_SCANCODE_RIGHT))
            return 1;
        if (GetKeyDown(SDL_SCANCODE_A) || GetKeyDown(SDL_SCANCODE_LEFT))
            return -1;
    case VERTICAL:
        if (GetKeyDown(SDL_SCANCODE_W) || GetKeyDown(SDL_SCANCODE_UP))
            return 1;
        if (GetKeyDown(SDL_SCANCODE_S) || GetKeyDown(SDL_SCANCODE_DOWN))
            return -1;
    default:
        return 0;
    }
    return 0;
}

void Input::KeyUp(SDL_KeyboardEvent *event) {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::KeyDown(SDL_KeyboardEvent *event) {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
}
