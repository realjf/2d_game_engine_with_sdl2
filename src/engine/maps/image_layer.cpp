#include "image_layer.h"
#include "graphics/texture_manager.h"

ImageLayer::ImageLayer(std::string textureID, int x, int y, float scrollRatio, float scalex, float scaley) {
    m_TextureID = textureID;
    m_OffsetX = x;
    m_OffsetY = y;
    m_ScrollRatio = scrollRatio;
    m_Repeated = true;
    m_ScaleX = scalex;
    m_ScaleY = scaley;
    QueryImage(m_TextureID);
}

void ImageLayer::QueryImage(std::string textureID) {
    SDL_Texture *texture = TextureManager::GetInstance()->GetTexture(textureID);
    SDL_QueryTexture(texture, nullptr, nullptr, &m_ImageWidth, &m_ImageHeight);
}

void ImageLayer::Render() {
    TextureManager::GetInstance()->Draw(m_TextureID, m_OffsetX, m_OffsetY, m_ImageWidth, m_ImageHeight, m_ScaleX, m_ScaleY);
}

void ImageLayer::Update() {
}
