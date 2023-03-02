#include "engine.h"
#include "graphics/texture_manager.h"
#include "physics/transform.h"
#include "characters/warrior.h"
#include "inputs/input.h"
#include "timer/timer.h"

Engine *Engine::s_Instance = nullptr;
Warrior *warrior = nullptr;

Engine::~Engine() {
}

bool Engine::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 && IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    m_Window = SDL_CreateWindow("2d game engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (m_Window == nullptr) {
        SDL_Log("Failed to create SDL window: %s", SDL_GetError());
        return false;
    }
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr) {
        SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
        return false;
    }

    TextureManager::GetInstance()->Load("viking_run", "assets/viking_800x710.png");
    TextureManager::GetInstance()->Load("viking_idle", "assets/viking2_idle800x710.png");
    TextureManager::GetInstance()->Load("viking_jump", "assets/viking2_800x710.png");

    warrior = new Warrior(new Properties("viking_idle", 100, 100, 800, 710, 0.1f));
    return m_IsRunning = true;
}

bool Engine::Clean() {

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
    warrior->Update(dt);
}

void Engine::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    warrior->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
    Input::GetInstance()->Listen();
}