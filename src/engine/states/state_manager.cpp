#include "state_manager.h"

void StateManager::PopState() {
    m_Completed = false;
    if (!m_States.empty()) {
        GameState *state = m_States.back();
        state->Exit();
        m_States.pop_back();
        delete state;
    }
    m_Completed = true;
}

void StateManager::PushState(GameState *state) {
    m_Completed = false;
    state->Init();
    m_States.push_back(state);
    m_Completed = true;
}

void StateManager::ChangeState(GameState *state) {
    m_Completed = false;
    if (!m_States.empty()) {
        GameState *state = m_States.back();
        state->Exit();
        m_States.pop_back();
        delete state;
    }
    state->Init();
    m_States.push_back(state);
    m_Completed = true;
}

void StateManager::Clean() {
    m_Completed = false;
    for (auto state : m_States) {
        state->Exit();
        delete state;
    }
}

void StateManager::Update() {
    if (m_Completed)
        m_States.back()->Update();
}

void StateManager::Render() {
    if (m_Completed)
        m_States.back()->Render();
}
