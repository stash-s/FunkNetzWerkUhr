#pragma once

#include <Arduino.h>

#include "clock_config.h"
#include "display.h"

<<<<<<< HEAD:funknetzwerkuhr/src/nixie_display.h
#define AUSF_A 1
#define AUSF_C 2

#ifdef NIXIE_VARIANT_AUSF_A
#  define NIXIE_VARIANT AUSF_A
#endif
#ifdef NIXIE_VARIANT_AUSF_C
#  define NIXIE_VARIANT AUSF_C
#endif
#ifndef NIXIE_VARIANT
#  define NIXIE_VARIANT AUSF_A
#endif


#define DISPLAY_HW_CLASS NixieDisplay
=======
#if defined(AUSF_B)
const int BLINK_LED = 2;
const int SHDN_PIN = 4;
const int LATCH_PIN = 15;

#elif defined(AUSF_C)
const int BLINK_LED = 2;
const int SHDN_PIN = 4;
const int LATCH_PIN = 15;
>>>>>>> origin/hardware-reset:funknetzwerkuhr/src/max_display.h

#else
const int BLINK_LED = 2;
const int SHDN_PIN = 4;
const int LATCH_PIN = 15;

#endif


<<<<<<< HEAD:funknetzwerkuhr/src/nixie_display.h
class NixieDisplay : public Display {
=======
#define MAX_DIGITS 4

class MaxDisplay : public Display {
>>>>>>> origin/hardware-reset:funknetzwerkuhr/src/max_display.h


public:
    typedef uint32_t payload_t;

    NixieDisplay ();
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