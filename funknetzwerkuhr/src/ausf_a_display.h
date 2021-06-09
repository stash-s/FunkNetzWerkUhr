#pragma once

#include <Arduino.h>

#include "clock_config.h"

#include "display.h"

const int SHDN_PIN = D2;
const int FILAMENT_PIN = D1;

#define MAX_DIGITS 4

class AusfADisplay : public Display {


public:
    typedef uint32_t payload_t;

    AusfADisplay ();
    virtual void init();

    virtual void shutdown ();
    virtual void setDigit (unsigned int digit, uint8_t value);
    virtual void setColor (uint8_t red, uint8_t green, uint8_t blue, bool pulseColors=true);

    virtual void setBrightness (uint8_t brightness);

    virtual void handle();

  private:

    static bool    _animate;
    static uint8_t _digits[MAX_DIGITS];
    static uint8_t _slot_effect[MAX_DIGITS];

    static uint8_t _pwm;

    friend void ausf_a_tick (/* arguments */);
    friend uint8_t ausf_a_get_digit (unsigned int);
};