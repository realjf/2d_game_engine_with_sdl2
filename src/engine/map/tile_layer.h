#ifndef _TILE_LAYER_H_
#define _TILE_LAYER_H_

#include <string>
#include <vector>
#include "layer.h"

struct Tileset {
    int First, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer {
public:
    TileLayer(int tileSize, int rowCount, int colCount, TileMap tilemap, TilesetList tilesets);
    virtual void Render();
    virtual void Update();
    inline TileMap GetTilemap() { returnm_Tilemap; }

private:
    int m_TileSize;
    int m_RowCount, m_ColCount;

    TileMap m_Tilemap;
    TilesetList m_Tilesets;
};

#endif /* _TILE_LAYER_H_ */
