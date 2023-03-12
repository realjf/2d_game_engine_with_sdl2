#include "play_state.h"
#include "engine.h"
#include "collision/collision_manager.h"
#include "characters/warrior.h"
#include "characters/enemy.h"
#include "menu_state.h"

PlayState::PlayState() {
}

void PlayState::Events() {
    SDL_Delay(100);
}

bool PlayState::Init() {
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    if (!TextureManager::GetInstance()->ParseTextures("assets/data/textures.xml")) {
        std::cout << "Failed to load textures" << std::endl;
        return false;
    }
    if ((m_Map = MapParser::GetInstance()->Load("assets/maps/map.tmx")) == nullptr) {
        std::cout << "Failed to load map" << std::endl;
        return false;
    }
    TileLayer *collisionLayer = (TileLayer *)m_Map->GetMapLayers().back();

    int tileSize = collisionLayer->GetTileSize();
    int width = collisionLayer->GetWidth() * tileSize;
    int height = collisionLayer->GetHeight() * tileSize;

    Camera::GetInstance()->SetSceneLimit(width, height);
    CollisionManager::GetInstance()->SetCollisionMap(collisionLayer->GetTileMap(), tileSize);

    Properties *props = new Properties("player_idle", 100, 100, 800, 710, 0.1f);
    GameObject *player = ObjectFactory::GetInstance()->CreateObject("PLAYER", props);
    Properties *props2 = new Properties("boss_idle", 400, 100, 800, 710, 0.1f);
    GameObject *enemy = ObjectFactory::GetInstance()->CreateObject("BOSS", props2);
    m_GameObjects.push_back(player);
    m_GameObjects.push_back(enemy);
    Camera::GetInstance()->SetTarget(player->GetOrigin());

    // Gui::GetInstance()->Init();
    std::cout << "play state init!" << std::endl;
    return true;
}

bool PlayState::Exit() {
    m_Map->Clean();
    delete m_Map;

    for (auto gameobj : m_GameObjects) {
        gameobj->Clean();
        delete gameobj;
    }

    m_GameObjects.clear();
    TextureManager::GetInstance()->Clean();
    std::cout << "play state exit!" << std::endl;
    return true;
}

void PlayState::Update() {
    Events();

    float dt = Timer::GetInstance()->GetDeltaTime();
    for (auto gameobj : m_GameObjects)
        gameobj->Update(dt);

    Camera::GetInstance()->Update(dt);
    m_Map->Update();
}

void PlayState::Render() {
    // SDL_SetRenderDrawColor(m_Ctxt, 48, 96, 130, 255);
    // SDL_RenderClear(m_Ctxt);

    m_Map->Render();

    for (auto gameobj : m_GameObjects)
        gameobj->Draw();

    SDL_Rect camera = Camera::GetInstance()->GetViewBox();

    SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
    // SDL_RenderPresent(m_Ctxt);
}

void PlayState::OpenMenu() {
    Engine::GetInstance()->GetStateManager()->ChangeState(new MenuState());
}

void PlayState::PauseGame() {
}
