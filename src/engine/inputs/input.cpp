#include "input.h"
#include "engine.h"

Input *Input::s_Instance = nullptr;

Input::Input() {
    m_KeyStates = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i < 3; i++) {
        m_MouseButtonStates.push_back(false);
    }
    m_MousePosition = Vector2D(0, 0);
    m_MouseLastPosition = Vector2D(0, 0);
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
        case SDL_MOUSEBUTTONDOWN:
            MouseButtonDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            MouseButtonUp(event);
            break;
        case SDL_MOUSEMOTION:
            MouseMotion(event);
            break;
        }
    }
}

bool Input::GetKeyDown(SDL_Scancode key) {
    if (m_KeyStates[key] == 1)
        return true;

    return false;
}

Dir Input::GetDirectionKey() {
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

void Input::MouseMotion(SDL_Event event) {
    SetMousePosition(static_cast<float>(event.motion.x), static_cast<float>(event.motion.y));
}

void Input::MouseButtonUp(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        SetMouseButtonState(MOUSE_LEFT, false);
        // std::cout << "mouse left released\n";
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        SetMouseButtonState(MOUSE_MIDDLE, false);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        SetMouseButtonState(MOUSE_RIGHT, false);
        // std::cout << "mouse right released\n";
    }
}

void Input::MouseButtonDown(SDL_Event event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        SetMouseButtonState(MOUSE_LEFT, true);
        // std::cout << "mouse left clicked\n";
    }
    if (event.button.button == SDL_BUTTON_MIDDLE) {
        SetMouseButtonState(MOUSE_MIDDLE, true);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
        SetMouseButtonState(MOUSE_RIGHT, true);
        // std::cout << "mouse right clicked\n";
    }
}
