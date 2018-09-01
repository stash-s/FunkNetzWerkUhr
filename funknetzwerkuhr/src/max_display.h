#ifndef __MAX_DISPLAY_H__
#define __MAX_DISPLAY_H__

#include <Arduino.h>

#include "clock_config.h"




#define MAX_DIGITS 4
#define RGB_MASK   0b000011100000000000000000
#define RED_MASK   0b000011000000000000000000
#define GREEN_MASK 0b000010100000000000000000
#define BLUE_MASK  0b000001100000000000000000


class MaxDisplay {


public:
    typedef uint32_t payload_t;

    MaxDisplay ();
    void init();

    void shutdown ();
    void setDigit (unsigned int digit, uint8_t value);
    void setColor (uint8_t red, uint8_t green, uint8_t blue);


private:

    static uint8_t _red;
    static uint8_t _green;
    static uint8_t _blue;
    static uint8_t _digits[MAX_DIGITS];

    static uint8_t _pwm;

    friend void tick (/* arguments */);
};

#endif //  __MAX_DISPLAY_H__
