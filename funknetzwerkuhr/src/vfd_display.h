#ifndef __MAX_DISPLAY_H__
#define __MAX_DISPLAY_H__

#include <Arduino.h>

#include "clock_config.h"

#include "display.h"


#define DISPLAY_HW_CLASS VfdDisplay

#define MAX_DIGITS 4


class VfdDisplay : public Display {


public:
    typedef uint32_t payload_t;

    VfdDisplay ();
    virtual void init() override;

    virtual void shutdown ();
    virtual void setDigit (unsigned int digit, uint8_t value) override;

    virtual void startAnimation () override;
    virtual void stopAnimation () override;
    virtual void setBrightness (uint8_t brightness) override;

private:

    static bool    _pulse_colors;
    static uint8_t _digits[MAX_DIGITS];
    static uint8_t _slot_effect[MAX_DIGITS];

    static uint8_t _pwm;

    friend void tick (/* arguments */);
    friend uint8_t get_digit (unsigned int);
};

#endif //  __MAX_DISPLAY_H__
