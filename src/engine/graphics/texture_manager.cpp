#include "texture_manager.h"
#include "engine.h"
#include <iostream>
#include "camera/camera.h"
#include <tinyxml.h>

TextureManager *TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string filename) {
    if (m_TextureMap.count(id) > 0) {
        std::cout << id << " already loaded!" << std::endl;
        return true;
    }

    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    SDL_FreeSurface(surface);
    std::cout << "Loaded texture: " << filename << std::endl;
    return true;
}

bool TextureManager::ParseTextures(std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source.c_str());
    if (xml.Error()) {
        std::cout << "Failed to load texture: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("texture")) {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id, src);
        }
    }

    std::cout << "Loaded texture success!" << std::endl;
    return true;
}

SDL_Texture *TextureManager::Load(std::string filename) {
    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        SDL_Log("Failed to load texture: %s, %s", filename.c_str(), SDL_GetError());
        return nullptr;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == nullptr) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return nullptr;
    }

    SDL_FreeSurface(surface);
    std::cout << "Loaded texture: " << filename << std::endl;
    return texture;
}

void TextureManager::Drop(std::string id) {
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean() {
    std::map<std::string, SDL_Texture *>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    m_TextureMap.clear();

    SDL_Log("texture map clean!");
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float xScale, float yScale, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {0, 0, width, height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), static_cast<int>(width * xScale), static_cast<int>(height * yScale)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, float xScale, float yScale, int row, int frame, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {width * frame, height * row, width, height};

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), static_cast<int>(width * xScale), static_cast<int>(height * yScale)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip) {
    SDL_Rect srcRect = {tileSize * frame, tileSize * row, tileSize, tileSize};

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), tileSize, tileSize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Draw(Transform *tf) {
    SDL_Rect srcRect = {0, 0, tf->Width, tf->Height};
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {static_cast<int>(tf->X - cam.X), static_cast<int>(tf->Y - cam.Y), static_cast<int>(tf->Width * tf->ScaleX), static_cast<int>(tf->Height * tf->ScaleY)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tf->TextureID], &srcRect, &dstRect, 0, nullptr, tf->Flip);
}

void TextureManager::DrawFrame(Transform *tf, int row, int frame) {
    SDL_Rect srcRect = {tf->Width * frame, tf->Height * row, tf->Width, tf->Height};

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect dstRect = {static_cast<int>(tf->X - cam.X), static_cast<int>(tf->Y - cam.Y), static_cast<int>(tf->Width * tf->ScaleX), static_cast<int>(tf->Height * tf->ScaleY)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tf->TextureID], &srcRect, &dstRect, 0, nullptr, tf->Flip);
}

void TextureManager::QueryTexture(std::string textureID, int *width, int *height) {
    SDL_QueryTexture(m_TextureMap[textureID], nullptr, nullptr, width, height);
}
