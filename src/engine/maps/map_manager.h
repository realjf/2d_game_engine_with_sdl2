#ifndef _MAP_MANAGER_H_
#define _MAP_MANAGER_H_

#include <vector>
#include <SDL.h>
#include "object/game_object.h"
#include "tile_map.h"
#include "weather/weather.h"

class MapManager {
public:
    virtual ~MapManager();

    void Init();
    void Clean();
    void Render();
    void Update();

    void SetTileMap(TileMap *tilemap);
    void SetWeather(WeatherState state);

    static MapManager *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapManager(); }

private:
    MapManager();
    SDL_Color m_BgColor;
    Weather *m_Weather;
    TileMap *m_TileMap;
    std::vector<GameObject *> m_GameObjects;

    static MapManager *s_Instance;
};

#endif /* _MAP_MANAGER_H_ */
