#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

#include <SDL.h>
#include <vector>
#include "maps/tile_layer.h"
#include "maps/game_map.h"
#include "engine.h"

class CollisionManager {
public:
    bool CheckCollision(SDL_Rect a, SDL_Rect b);
    bool MapCollision(SDL_Rect a);

    inline void SetCollisionMap(TileMap map, TileLayer *layer) {
        m_CollisionTileMap = map;
        m_CollisionLayer = layer;
    }

    inline static CollisionManager *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new CollisionManager(); }

private:
    CollisionManager();
    TileMap m_CollisionTileMap;
    TileLayer *m_CollisionLayer;
    static CollisionManager *s_Instance;
};

#endif /* _COLLISION_MANAGER_H_ */
