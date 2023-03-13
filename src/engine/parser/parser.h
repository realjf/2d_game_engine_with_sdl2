#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <tinyxml.h>
#include "maps/tile_map.h"
#include "maps/tile_layer.h"

class Parser {
public:
    static Parser *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Parser(); }

    bool ParseSounds(std::string source);
    bool ParseTextures(std::string source);
    bool ParseFonts(std::string source);
    bool ParseGameObjects(std::string source);
    TileMap *ParseMap(std::string source);

private:
    Tileset ParseEmbedTileset(TiXmlElement *xmlTileset);
    Tileset ParseOutsideTileset(TiXmlElement *xmlTileset);
    TileLayer *ParseTileLayer(TiXmlElement *xmlLayer, std::vector<Tileset> tilesets, int tileSize, int rowCount, int colCount);
    std::string ExtractMapDir(const char *levelFile);

    inline std::string GetMapDir() {
        return m_MapDir;
    }

private:
    std::string m_MapDir;
    static Parser *s_Instance;
};

#endif /* _PARSER_H_ */
