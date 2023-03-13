#ifndef _WEATHER_MANAGER_H_
#define _WEATHER_MANAGER_H_

#include <vector>
#include "weather.h"

class WeatherManager {
public:
    static WeatherManager *GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new WeatherManager(); }

    void Init();
    void Update();
    void Render();
    void Clean();

private:
    WeatherManager() {}

private:
    std::vector<Weather *> m_Weathers;
    static WeatherManager *s_Instance;
};

#endif /* _WEATHER_MANAGER_H_ */
