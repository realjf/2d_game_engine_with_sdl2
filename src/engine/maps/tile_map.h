#ifndef _TILE_MAP_H_
#define _TILE_MAP_H_

#include <vector>
#include "layer.h"

class TileMap {
public:
    TileMap() {}

    void Render() {
        for (auto layer : m_MapLayers)
            layer->Render();
    }

    void Update() {
        for (auto layer : m_MapLayers)
            layer->Update();
    }

    void Clean() {
        for (auto layer : m_MapLayers)
            delete layer;
        m_MapLayers.clear();
    }

    inline void PushLayer(Layer *layer) {
        m_MapLayers.push_back(layer);
    }

    std::vector<Layer *> GetLayers() {
        return m_MapLayers;
    }

private:
    friend class Parser;
    std::vector<Layer *> m_MapLayers;
};

#endif /* _TILE_MAP_H_ */
