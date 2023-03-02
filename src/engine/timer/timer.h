#ifndef _TIMER_H_
#define _TIMER_H_

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer {
public:
    void Tick();
    inline float GetDeltaTime() { return m_DeltaTime; }
    inline float GetLastTime() { return m_LastTime; }
    inline static Timer *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }

private:
    Timer() {}
    static Timer *s_Instance;
    float m_DeltaTime;
    float m_LastTime;
};
#endif /* _TIMER_H_ */
