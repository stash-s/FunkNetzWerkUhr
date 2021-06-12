#include <Arduino.h>
#include "delay.hpp"

void Delay::delay(std::function<void()> action, unsigned int delay_time) {
    auto millis_now = millis();
    _due_time = millis_now + delay_time;
    _action = action;
}

void Delay::handle () {
    if (_action) {
        auto millis_now = millis();
        if (millis_now >= _due_time) {
            _action();
            _action = 0;
        }
    }
}