#include "parser.h"
#include "sounds/sound_manager.h"
#include "graphics/texture_manager.h"

Parser *Parser::s_Instance = nullptr;

bool Parser::ParseSounds(std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source.c_str());
    if (xml.Error()) {
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("effect")) {
            SoundManager::GetInstance()->LoadEffect(e->Attribute("id"), e->Attribute("source"));
            continue;
        }

        if (e->Value() == std::string("music")) {
            SoundManager::GetInstance()->LoadMusic(e->Attribute("id"), e->Attribute("source"));
            continue;
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return true;
}

bool Parser::ParseTextures(std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source.c_str());
    if (xml.Error()) {
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("texture")) {
            std::string id = e->Attribute("id");
            std::string source = e->Attribute("source");
            TextureManager::GetInstance()->Load(id, source);
        }
    }

    std::cout << source << " Parsed!" << std::endl;
    return true;
}

bool Parser::ParseFonts(std::string source)
{

}

bool Parser::ParseGameObjects(std::string source)
{

}

TileMap *Parser::ParseMap(std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source.c_str());
    ExtractMapDir(source.c_str());
    if (xml.Error()) {
        std::cout << "Failed to load: " << source << std::endl;
        return nullptr;
    }

    TiXmlElement *root = xml.RootElement();
    int colCount, rowCount, tileSize = 0;
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
    TileMap *gameMap = new TileMap();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("layer")) {
            TileLayer *tilelayer = ParseTileLayer(e, tilesets, tileSize, rowCount, colCount);
            gameMap->PushLayer(tilelayer);
        }
    }

    return gameMap;
}

Tileset Parser::ParseEmbedTileset(TiXmlElement *xmlTileset) {
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

Tileset Parser::ParseOutsideTileset(TiXmlElement *xmlTileset) {
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

TileLayer *Parser::ParseTileLayer(TiXmlElement *xmlLayer, std::vector<Tileset> tilesets, int tileSize, int rowCount, int colCount) {
    TiXmlElement *data = nullptr;
    for (TiXmlElement *e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("data")) {
            data = e;
            break;
        }
    }

    if (data == nullptr) {
        std::cout << "ERROR: Could not found data" << std::endl;
        return nullptr;
    }

    // parse layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMatrix tilemap(rowCount, std::vector<int>(colCount, 0));

    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < colCount; col++) {
            std::getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            // std::cout << tilemap[row][col] << ",";

            if (!iss.good())
                break;
        }
        // std::cout << std::endl;
    }

    return (new TileLayer(tileSize, rowCount, colCount, tilemap, tilesets));
}

std::string Parser::ExtractMapDir(const char *levelFile) {
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
