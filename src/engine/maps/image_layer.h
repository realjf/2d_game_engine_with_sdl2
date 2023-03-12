#ifndef _IMAGE_LAYER_H_
#define _IMAGE_LAYER_H_

#include <iostream>
#include <string>
#include "layer.h"
#include <SDL.h>
#include <SDL_image.h>

class ImageLayer : public Layer {
public:
    ImageLayer(std::string textureID, int x, int y, float scrollRatio = 1.0f, float scalex = 1.0f, float scaley = 1.0f);
    void SetScrollRatio(float scrollRatio) { m_ScrollRatio = scrollRatio; }
    void SetOffset(int x, int y) {
        m_OffsetX = x;
        m_OffsetY = y;
    }
    void SetRepeated(bool repeated) { m_Repeated = repeated; }
    void QueryImage(std::string textureID);

    virtual void Render();
    virtual void Update();

private:
    bool m_Repeated;
    float m_ScrollRatio;
    std::string m_TextureID;
    float m_ScaleX, m_ScaleY;
    int m_OffsetX, m_OffsetY;
    int m_ImageWidth, m_ImageHeight;
    SDL_RendererFlip m_Flip;
};

#endif /* _IMAGE_LAYER_H_ */
