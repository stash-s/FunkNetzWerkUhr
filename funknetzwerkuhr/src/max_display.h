#ifndef __MAX_DISPLAY_H__
#define __MAX_DISPLAY_H__

#include <Arduino.h>

#include "clock_config.h"

#include "display.h"



#define MAX_DIGITS 4

class MaxDisplay : public Display {


public:
    typedef uint32_t payload_t;

    MaxDisplay ();
    virtual void init();

    virtual void shutdown ();
    virtual void setDigit (unsigned int digit, uint8_t value);
    virtual void setColor (uint8_t red, uint8_t green, uint8_t blue, bool pulseColors=true);

    virtual void setBrightness (uint8_t brightness);

private:

    static bool    _pulse_colors;
    static uint8_t _red;
    static uint8_t _green;
    static uint8_t _blue;
    static uint8_t _digits[MAX_DIGITS];
    static uint8_t _slot_effect[MAX_DIGITS];

    static uint8_t _pwm;

    friend void tick (/* arguments */);
    friend uint8_t get_digit (unsigned int);
};

#endif //  __MAX_DISPLAY_H__
