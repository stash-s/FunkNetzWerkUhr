#include <Arduino.h>
#include "light_sensor.h"

#define LIGHT_LEVEL_MAX 11
static const unsigned int light_level_bounds[]
    = { 200,300,400,500,600,700,785,830,900,990,1023 };
static const size_t pwm_level[]={32,32,32,32,32,24,16,8,6,4,2};

LightSensor::LightSensor ()
    :_readingHandler ([](int i){}),
     _levelHandler ([](int i){}) {

}

void LightSensor::onReading(std::function<void(int)> handler) {
    _readingHandler = handler;
}

void LightSensor::onLevelSet (std::function<void(int)> handler) {
    _levelHandler = handler;
}

inline size_t map_adc_to_level (size_t adc) {
    for (int i=0; i < LIGHT_LEVEL_MAX; ++i) {
        if (light_level_bounds[i] >= adc) {
            return pwm_level[i];
        }
    }
    return pwm_level[LIGHT_LEVEL_MAX];
}

void LightSensor::handle() {
    static auto last_millis = millis();
    auto current_millis = millis();

    if (current_millis - last_millis >= 100) {
        last_millis = current_millis;

        auto value = analogRead (A0);
        auto lightLevel = map_adc_to_level(value);

        _readingHandler (value);
        _levelHandler (lightLevel);
    }
}
