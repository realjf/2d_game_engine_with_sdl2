#include "collision_manager.h"

CollisionManager *CollisionManager::s_Instance = nullptr;

bool CollisionManager::CheckCollision(SDL_Rect a, SDL_Rect b) {
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return (x_overlaps && y_overlaps);
}

bool CollisionManager::MapCollision(SDL_Rect a) {

    int left_tile = a.x / m_MapTileSize;
    int right_tile = (a.x + a.w) / m_MapTileSize;

    int top_tile = a.y / m_MapTileSize;
    int bottom_tile = (a.y + a.h) / m_MapTileSize;

    if (left_tile < 0)
        left_tile = 0;

    if (right_tile > m_MapWidth)
        right_tile = m_MapWidth;

    if (top_tile < 0)
        top_tile = 0;

    if (bottom_tile > m_MapHeight)
        bottom_tile = m_MapHeight;

    for (int i = left_tile; i <= right_tile; ++i) {
        for (int j = top_tile; j <= bottom_tile; ++j) {
            if (m_CollisionTileMap[j][i] > 0) {
                return true;
            }
        }
    }

    return false;
}

void CollisionManager::SetCollisionMap(TileMatrix map, int m_MapTileSize) {
    m_CollisionTileMap = map;
    m_MapTileSize = m_MapTileSize;
    m_MapHeight = map.size();
    m_MapWidth = map[0].size();
}

CollisionManager::CollisionManager() {
}
