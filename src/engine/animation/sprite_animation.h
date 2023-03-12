#ifndef _SPRITE_ANIMATION_H_
#define _SPRITE_ANIMATION_H_

#include "animation.h"

class SpriteAnimation : public Animation {
public:
    SpriteAnimation(bool repeat = true);

    virtual void Update(float dt);
    void Draw(float x, float y, int width, int height, float scale, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetCurrentFrame(int frame) { m_CurrentFrame = frame; }
    void SetSpriteRow(int row) { m_SpriteRow = row; }
    int GetCurrentFrame() { return m_CurrentFrame; }
    int GetSpriteRow() { return m_SpriteRow; }
    int GetSpeed() { return m_Speed; }
    int GetFrameCount() { return m_FrameCount; }
    void IncrSpriteRow() { m_SpriteRow++; }
    void DecrSpriteRow() { m_SpriteRow--; }

private:
    int m_SpriteRow;
    int m_Speed;
    int m_FrameCount;
    std::string m_TextureID;
    SDL_RendererFlip m_Flip;
};

#endif /* _SPRITE_ANIMATION_H_ */
