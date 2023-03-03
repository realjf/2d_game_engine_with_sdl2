#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_

#include <vector>
#include "layer.h"

class GameMap {
public:
    void Render() {
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

private:
    std::vector<Layer *> m_MapLayers;
};

#endif /* _GAME_MAP_H_ */
