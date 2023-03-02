#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include <SDL.h>

class Animation {
public:
    Animation() {}

    void Update(bool defaultAnim = true);
    void Draw(float x, float y, int spriteWidth, int spriteHeight, float scale);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetSpriteFrame(int frame) { m_SpriteFrame = frame; }
    void SetSpriteRow(int row) { m_SpriteRow = row; }
    int GetSpriteRow() { return m_SpriteRow; }
    int GetAnimSpeed() { return m_AnimSpeed; }
    int GetFrameCount() { return m_FrameCount; }

private:
    int m_SpriteRow, m_SpriteFrame;
    int m_AnimSpeed, m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};

#endif /* _ANIMATION_H_ */
