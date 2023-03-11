#include "map_parser.h"
#include <filesystem>
#include "engine.h"

MapParser *MapParser::s_Instance = nullptr;

bool MapParser::Load() {
    return Parse("level1", "assets/maps/map.tmx");
}

void MapParser::Clean() {
    std::map<std::string, GameMap *>::iterator it;
    for (it = m_Maps.begin(); it != m_Maps.end(); it++) {
        it->second = nullptr;
    }
    m_Maps.clear();
}

bool MapParser::Parse(std::string id, std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source.c_str());
    ExtractMapDir(source.c_str());

    if (xml.Error()) {
        std::cout << "Error: Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    int rowCount, colCount, tileSize = 0;

    root->Attribute("width", &colCount);
    root->Attribute("height", &rowCount);
    root->Attribute("tilewidth", &tileSize);

    // parse tileset
    TilesetList tilesets;
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("tileset")) {
            if (e->HasAttribute("source") != TIXML_SUCCESS) {
                tilesets.push_back(ParseEmbedTileset(e));
            } else {
                tilesets.push_back(ParseOutsideTileset(e));
            }
        }
    }

    // parse layers
    GameMap *gameMap = new GameMap();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            TileLayer *tilelayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
            gameMap->GetMapLayers().push_back(tilelayer);
        }
    }

    m_Maps[id] = gameMap;
    return true;
}

Tileset MapParser::ParseEmbedTileset(TiXmlElement *xmlTileset) {
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement *image = xmlTileset->FirstChildElement();
    tileset.Source = GetMapDir() + "/" + image->Attribute("source");

    return tileset;
}

Tileset MapParser::ParseOutsideTileset(TiXmlElement *xmlTileset) {
    Tileset tileset;

    xmlTileset->Attribute("firstgid", &tileset.FirstID);

    // outside the map
    // create a tinyxml document and load the map(*.tmx)
    TiXmlDocument tsxDocument;
    std::string tsxFile = GetMapDir() + "/" + xmlTileset->Attribute("source");
    tsxDocument.LoadFile(tsxFile.c_str());

    // get the root node
    TiXmlElement *pTilesetRoot = tsxDocument.RootElement();

    tileset.Name = pTilesetRoot->Attribute("name");

    std::cout << GetMapDir() << std::endl;

    // first and the tileset to texture manager
    std::string tilesetImage = GetMapDir() + "/" + pTilesetRoot->FirstChildElement()->Attribute("source");
    tileset.Source = tilesetImage;

    pTilesetRoot->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    pTilesetRoot->Attribute("columns", &tileset.ColCount);
    tileset.RowCount = tileset.TileCount / tileset.ColCount;
    pTilesetRoot->Attribute("tilewidth", &tileset.TileSize);

    return tileset;
}

TileLayer *MapParser::ParseTileLayer(TiXmlElement *xmlLayer, std::vector<Tileset> tilesets, int tileSize, int rowCount, int colCount) {
    TiXmlElement *data;
    for (TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
        }
    }

    // parse layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMap tilemap(rowCount, std::vector<int>(colCount, 0));

    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if (!iss.good())
                break;
        }
    }

    return (new TileLayer(tileSize, rowCount, colCount, tilemap, tilesets));
}

std::string MapParser::ExtractMapDir(const char *levelFile) {
    std::string path(levelFile);
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    static const std::string slash = "\\";
#else
    static const std::string slash = "/";
#endif
    const size_t lastSlashIdx = path.rfind(slash);
    if (std::string::npos != lastSlashIdx) {
        m_MapDir = path.substr(0, lastSlashIdx);
    }

    return path.substr(0, lastSlashIdx);
}
