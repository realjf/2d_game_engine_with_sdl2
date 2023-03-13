#include "map_manager.h"
#include "parser/parser.h"
#include "sounds/sound_manager.h"
#include "timer/timer.h"
#include "camera/camera.h"
#include "graphics/texture_manager.h"

MapManager *MapManager::s_Instance = nullptr;

MapManager::~MapManager() {
}

void MapManager::Init() {
    Parser::GetInstance()->ParseSounds("asssets/data/sounds.xml");
    Parser::GetInstance()->ParseTextures("asssets/data/textures.xml");
    m_TileMap = Parser::GetInstance()->ParseMap("asssets/maps/map.tmx");

    m_Weather = new Weather(WeatherState::Cloudy);
}

void MapManager::Clean() {
    SoundManager::GetInstance()->Clean();
    TextureManager::GetInstance()->Clean();
}

void MapManager::Render() {
    for (auto obj : m_GameObjects)
        obj->Draw();

    m_TileMap->Render();
    m_Weather->Render();
}

void MapManager::Update() {
    float dt = Timer::GetInstance()->GetDeltaTime();
    for (auto obj : m_GameObjects)
        obj->Update(dt);

    m_TileMap->Update();
    m_Weather->Update(dt);
}

void MapManager::SetTileMap(TileMap *tilemap) {
    if (tilemap != nullptr) {
        m_TileMap->Clean();
        m_TileMap = tilemap;
        return;
    }
    std::cout << "Failed to set tilemap!" << std::endl;
}

void MapManager::SetWeather(WeatherState state) {
}

MapManager::MapManager() {
}
