#ifndef _MAP_PARSER_H_
#define _MAP_PARSER_H_

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include "tile_map.h"
#include "tile_layer.h"
#include <tinyxml.h>

class MapParser {
public:
    static MapParser *GetInstance() {
        if (s_Instance == nullptr) {
            s_Instance = new MapParser();
        }
        return s_Instance;
    }

    TileMap *Load(std::string source);
    void Clean();
    inline TileMap *GetMap(std::string id) {
        return m_Maps[id];
    }

private:
    MapParser() {}
    bool Parse(std::string id, std::string source);
    Tileset ParseEmbedTileset(TiXmlElement *xmlTileset);
    Tileset ParseOutsideTileset(TiXmlElement *xmlTileset);
    TileLayer *ParseTileLayer(TiXmlElement *xmlLayer, std::vector<Tileset> tilesets, int tileSize, int rowCount, int colCount);
    std::string ExtractMapDir(const char *levelFile);

    inline std::string GetMapDir() {
        return m_MapDir;
    }

private:
    std::map<std::string, TileMap *> m_Maps;
    std::string m_MapDir;
    static MapParser *s_Instance;
};

#endif /* _MAP_PARSER_H_ */
