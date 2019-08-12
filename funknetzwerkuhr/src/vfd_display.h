#pragma once

#include <Arduino.h>

#include "clock_config.h"

#include "display.h"

//const int BLINK_LED = 2;
//const int SHDN_PIN = 4;


#define MAX_DIGITS 4


class VfdDisplay : public Display {


public:
    typedef uint32_t payload_t;

    VfdDisplay (const AppConfig & config);
    virtual void init() override;

    virtual void shutdown ();
    virtual void setDigit (unsigned int digit, uint8_t value) override;

    virtual void startAnimation () override;
    virtual void stopAnimation () override;
    virtual void setBrightness (uint8_t brightness) override;

    static uint8_t getDigit (unsigned int);

private:

    static bool    _pulse_colors;
    static uint8_t _digits[MAX_DIGITS];
    static uint8_t _slot_effect[MAX_DIGITS];

    static uint8_t _pwm;

    friend void tick (/* arguments */);
};

ICACHE_RAM_ATTR
inline
uint8_t VfdDisplay::getDigit (unsigned int digit) {
    return _digits[digit];
}

