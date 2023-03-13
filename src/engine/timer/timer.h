#ifndef _TIMER_H_
#define _TIMER_H_

#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_timer.h>

const int FPS = 60;
const float FRAME_PER_SECOND = FPS / 1000.0f;

const float FRAME_DELAY = 1000.0f / FPS;
const float MAX_DELTA_TIME = 1.5f;

using TimerID = SDL_TimerID;
using T_Callback = SDL_TimerCallback;

class Timer {
public:
    Timer();
    void Tick();
    inline float GetDeltaTime() { return m_DeltaTime; }
    inline float GetLastTime() { return m_LastTime; }
    inline static Timer *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

    inline void Clean() {
        for (TimerID id : m_TimerRegistry)
            SDL_RemoveTimer(id);
    }

    inline TimerID StartTimer(Uint32 interval, T_Callback callback, void *data) {
        TimerID id = SDL_AddTimer(interval, callback, data);
        m_TimerRegistry.push_back(id);
        return id;
    }

    inline void RemoveTimer(TimerID id) {
        SDL_RemoveTimer(id);
    }

private:
    static Timer *s_Instance;
    float m_DeltaTime;
    float m_LastTime;
    std::vector<TimerID> m_TimerRegistry;
};
#endif /* _TIMER_H_ */
