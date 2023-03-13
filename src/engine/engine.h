#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <memory>
#include <vector>
#include "maps/game_map.h"
#include "object/game_object.h"
#include "states/state_manager.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Engine {
public:
    virtual ~Engine();

    static Engine *GetInstance() {
        if (s_Instance == nullptr) {
            s_Instance = new Engine();
        }
        return s_Instance;
    }

    bool Init();
    bool Clean();
    void Quit();

    void Update();
    void Render();
    void Events();

    inline bool IsRunning() { return m_IsRunning; }
    inline SDL_Renderer *GetRenderer() { return m_Renderer; }
    inline StateManager *GetStateManager() { return m_StateManager; }
    inline SDL_Rect GetViewPort() {
        SDL_RenderGetViewport(m_Renderer, &m_ViewPort);
        return m_ViewPort;
    }

private:
    Engine() {
    }

private:
    bool m_IsRunning;
    SDL_Window *m_Window;
    SDL_Renderer *m_Renderer;
    std::vector<GameObject *> m_GameObjects;
    StateManager *m_StateManager;
    SDL_Rect m_ViewPort;
    static Engine *s_Instance;
};

#endif /* _ENGINE_H_ */
