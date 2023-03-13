#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

#include <map>
#include <string>
#include <iostream>
#include <SDL_mixer.h>

#define FREQ 44100
#define CHUNK_SIZE 2048

using EffectMap = std::map<std::string, Mix_Chunk *>;
using MusicMap = std::map<std::string, Mix_Music *>;

class SoundManager {
public:
    void Clean();

    void PlayMusic(std::string id);
    void LoadMusic(std::string id, std::string source);

    void PlayEffect(std::string id);
    void LoadEffect(std::string id, std::string source);

    inline static SoundManager *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new SoundManager(); }

private:
    SoundManager();
    MusicMap m_MusicMap;
    EffectMap m_EffectMap;
    static SoundManager *s_Instance;
};

#endif /* _SOUND_MANAGER_H_ */
