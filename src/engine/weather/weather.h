#ifndef _WEATHER_H_
#define _WEATHER_H_

enum class WeatherState {
    Cloudy,
    Sunny,
    Rainy,
    Snowy,
    Foggy,
    Windy,
    Lightning
};

class Weather {
public:
    Weather(WeatherState state);

    void Init();
    void Update(float dt);
    void Render();
    void Exit();

private:
    WeatherState m_State;
};

#endif /* _WEATHER_H_ */
