#pragma once

#include <Arduino.h>

#include "clock_config.h"
#include "display.h"

#define AUSF_A 1
#define AUSF_C 2
#define AUSF_D 3

#ifdef NIXIE_VARIANT_AUSF_A
#  define NIXIE_VARIANT AUSF_A
const int BLINK_LED = 2;
const int SHDN_PIN = 4;
#elif defined (NIXIE_VARIANT_AUSF_C)
#  define NIXIE_VARIANT AUSF_C
const int BLINK_LED = 2;
const int SHDN_PIN = 4;
#elif defined (NIXIE_VARIANT_AUSF_D)
#  define NIXIE_VARIANT AUSF_D
const int BLINK_LED = 2;
const int SHDN_PIN  = 16;
//#else
//#  error Unknown Nixie hardware variant.
#endif


#ifndef NIXIE_VARIANT
#  define NIXIE_VARIANT AUSF_A
#endif

#define MAX_DIGITS 4
#define RGB_MASK   0b000011100000000000000000
#define RED_MASK   0b000011000000000000000000
#define GREEN_MASK 0b000010100000000000000000
#define BLUE_MASK  0b000001100000000000000000


class NixieDisplay : public Display {


public:
    typedef uint32_t payload_t;

    NixieDisplay (const AppConfig &);
    virtual void init();

    virtual void shutdown ();
    virtual void setDigit (unsigned int digit, uint8_t value);
    virtual void setColor (uint8_t red, uint8_t green, uint8_t blue) override;

    virtual void startAnimation () override;
    virtual void stopAnimation () override;

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
