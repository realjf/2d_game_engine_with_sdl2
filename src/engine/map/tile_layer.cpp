#include "tile_layer.h"

TileLayer::TileLayer(int tileSize, int rowCount, int colCount, TileMap tilemap, TilesetList tilesets) {
    m_TileSize = tileSize;
    m_RowCount = rowCount;
    m_ColCount = colCount;
    m_Tilemap = tilemap;
    m_Tilesets = tilesets;
}

void TileLayer::Render() {
}

void TileLayer::Update() {
}
