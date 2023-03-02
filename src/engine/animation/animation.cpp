#include "animation.h"
#include "graphics/texture_manager.h"

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, float scale) {
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, scale, m_SpriteRow, m_SpriteFrame, m_Flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip) {
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_Flip = flip;
    m_AnimSpeed = animSpeed;
}

void Animation::Update(bool defaultAnim) {
    if (defaultAnim) {
        m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
    }
}
