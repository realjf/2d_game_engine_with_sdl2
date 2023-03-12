#include "sprite_animation.h"
#include "graphics/texture_manager.h"

void SpriteAnimation::Draw(float x, float y, int width, int height, float scale, SDL_RendererFlip flip) {
    if (flip != SDL_FLIP_NONE) {
        m_Flip = flip;
    }
    TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, width, height, scale, m_SpriteRow, m_CurrentFrame, m_Flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip) {
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_Flip = flip;
    m_Speed = animSpeed;
}

void SpriteAnimation::Update(float dt) {
    m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
}

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat) {
}
