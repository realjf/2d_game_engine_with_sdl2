#include "engine.h"
#include "graphics/texture_manager.h"
#include "physics/transform.h"
#include "characters/warrior.h"
#include "inputs/input.h"
#include "timer/timer.h"
#include "maps/map_parser.h"
#include "camera/camera.h"
#include "characters/enemy.h"
#include "factory/object_factory.h"
#include "states/menu_state.h"
#include "states/play_state.h"

Engine *Engine::s_Instance = nullptr;

Engine::~Engine() {
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    SDL_WindowFlags windowFlags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("2d game engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (m_Window == nullptr) {
        SDL_Log("Failed to create SDL window: %s", SDL_GetError());
        return false;
    }
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr) {
        SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
        return false;
    }

    m_StateManager = new StateManager();
    m_StateManager->PushState(new PlayState());

    return m_IsRunning = true;
}

bool Engine::Clean() {
    m_StateManager->Clean();

    TextureManager::GetInstance()->Clean();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    IMG_Quit();
    SDL_Quit();

    return true;
}

void Engine::Quit() {
    m_IsRunning = false;
}

void Engine::Update() {
    // SDL_Log("xxxxxxx");
    float dt = Timer::GetInstance()->GetDeltaTime();

    m_StateManager->Update();
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    m_StateManager->Render();

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    Input::GetInstance()->Listen();
}
