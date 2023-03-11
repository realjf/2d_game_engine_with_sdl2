#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <vector>
#include <iostream>
#include "layer.h"

class GameMap {
public:
    void Render() {
        // std::cout << "size: " << m_MapLayers.size() << std::endl;
        for (unsigned int i = 0; i < m_MapLayers.size(); i++) {
            m_MapLayers[i]->Render();
        }
    }

    void Update() {
        for (unsigned int i = 0; i < m_MapLayers.size(); i++) {
            m_MapLayers[i]->Update();
        }
    }

    std::vector<Layer *> GetMapLayers() { return m_MapLayers; }

    inline void PushLayer(Layer *layer) {
        m_MapLayers.push_back(layer);
    }

private:
    std::vector<Layer *> m_MapLayers;
};

#endif /* _GAME_MAP_H_ */
