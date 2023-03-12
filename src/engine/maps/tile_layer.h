#ifndef _TILE_LAYER_H_
#define _TILE_LAYER_H_

#include <string>
#include <vector>
#include "layer.h"

class Tileset {
public:
    int FirstID, LastID;
    int RowCount, ColCount;
    int TileCount, TileSize;
    std::string Name, Source;
};

// struct Tileset {
//     int FirstID, LastID;
//     int RowCount, ColCount;
//     int TileCount, TileSize;
//     std::string Name, Source;
// };

using TilesetList = std::vector<Tileset>;
using TileMap = std::vector<std::vector<int>>;

class TileLayer : public Layer {
public:
    TileLayer(int tileSize, int rowCount, int colCount, TileMap tilemap, TilesetList tilesets);
    virtual void Render();
    virtual void Update();
    inline TileMap GetTileMap() { return m_Tilemap; }
    inline int GetTileSize() { return m_TileSize; }
    inline int GetWidth() { return m_ColCount; }
    inline int GetHeight() { return m_RowCount; }

private:
    int m_TileSize;
    int m_RowCount, m_ColCount;

    TileMap m_Tilemap;
    TilesetList m_Tilesets;
};

#endif /* _TILE_LAYER_H_ */
