#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include "physics/transform.h"

using TextureMap = std::map<std::string, SDL_Texture *>;

class TextureManager {
public:
    static TextureManager *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new TextureManager(); }

    bool Load(std::string id, std::string filename);
    bool ParseTextures(std::string source);
    SDL_Texture *Load(std::string filename);
    void Drop(std::string id);
    void Clean();

    void Draw(std::string id, int x, int y, int width, int height, float xScale, float yScale, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawFrame(std::string id, int x, int y, int width, int height, float xScale, float yScale, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Draw(Transform *tf);
    void DrawFrame(Transform *tf, int row, int frame);

    inline SDL_Texture *GetTexture(std::string id) { return m_TextureMap[id]; }
    TextureMap GetTextureMap() { return m_TextureMap; }

    void QueryTexture(std::string textureID, int *width, int *height);

private:
    TextureManager() {}

private:
    TextureMap m_TextureMap;
    static TextureManager *s_Instance;
};

#endif /* _TEXTURE_MANAGER_H_ */
