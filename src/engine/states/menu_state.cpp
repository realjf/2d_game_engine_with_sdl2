#include "menu_state.h"
#include "engine.h"
#include "inputs/input.h"

MenuState::MenuState() {
}

bool MenuState::Init() {
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    std::cout << "menu state initialized!" << std::endl;
    return true;
}

bool MenuState::Exit() {
    std::cout << "menu state exited!" << std::endl;
    return true;
}

void MenuState::Update() {
}

void MenuState::Render() {
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_Ctxt);

    SDL_RenderPresent(m_Ctxt);
}

void MenuState::StartGame() {
    std::cout << "start game!" << std::endl;
}

void MenuState::ExitGame() {
    std::cout << "exit game!" << std::endl;
}

void MenuState::Settings() {
    std::cout << "settings!" << std::endl;
}

void MenuState::Editor() {
    std::cout << "editor!" << std::endl;
}
