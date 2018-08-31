
#include <SPI.h>

#include "clock_config.h"
#include "max_display.h"

#include <functional>

//static std::function<void (void)> isr_callback;


static MaxDisplay::payload_t payload=0;

uint8_t MaxDisplay::_red=0;
uint8_t MaxDisplay::_green=0;
uint8_t MaxDisplay::_blue=0;
uint8_t MaxDisplay::_digits[MAX_DIGITS];
uint8_t MaxDisplay::_pwm=PWM_INIT;

static int display_timer_divider=0;

ICACHE_RAM_ATTR
inline void setDataBits(uint16_t bits) {
    const uint32_t mask = ~((SPIMMOSI << SPILMOSI) | (SPIMMISO << SPILMISO));
    bits--;
    SPI1U1 = ((SPI1U1 & mask) | ((bits << SPILMOSI) | (bits << SPILMISO)));
}


MaxDisplay::MaxDisplay()
{}

static MaxDisplay::payload_t led_mux_map[] = {
    0b000100000000000000000000, // digit 1
    0b001000000000000000000000, // digit 2
    0b010000000000000000000000, // digit 3
    0b100000000000000000000000, // nope
};

static MaxDisplay::payload_t color_map[] = {
    0b000011000000000000000000, // red
    0b000010100000000000000000, // green
    0b000001100000000000000000, // blue
    0b000010100000000000000000, // green
    0b000011100000000000000000, // blank all
};


static MaxDisplay::payload_t dots_map[] = {
    0b000000000000000000000000, // dots off
    0b000000011000000000000000  // dots on
};


static MaxDisplay::payload_t digit_mux_map[] = {
    0b0001, // digit 1
    0b0010, // digit 2
    0b0100, // digit 3
    0b1000, // digit 4
};


static MaxDisplay::payload_t number_mux_map[] = {
    0b1000000000000, // number 0
    0b1000000000, // number 1
    0b100000000, // number 2
    0b10000000, // number 3
    0b10000, // number 4
    0b100000, // number 5
    0b100000000000000, // number 6
    0b100000000000, // number 7
    0b1000000, // number 8
    0b10000000000000, // number 9
//    0b10000000000, // dot
};



ICACHE_RAM_ATTR
void tick (/* arguments */) {
    static int current_digit=0;
    static int seconds_counter=0;
    static int pwm_counter=0;

    ++pwm_counter;
    if (pwm_counter >= PWM_MAX) {
        pwm_counter = 0;

        ++current_digit;
        if ( current_digit >= MAX_DIGITS ) {
             current_digit = 0;
        }

    } else {

        //MaxDisplay::payload_t anodes=0;

        static int dots_state = 0;
        ++ seconds_counter;
        if ( seconds_counter >= (display_timer_divider * 16) ) {
            seconds_counter = 0;
            dots_state = dots_state ? 0 : 1;
        }

        uint32_t color_mask = RGB_MASK;
        if (MaxDisplay::_red) color_mask &= RED_MASK;
        if (MaxDisplay::_green) color_mask &= GREEN_MASK;
        if (MaxDisplay::_blue) color_mask &= BLUE_MASK;

        // if pwm counter >= pwm, blank digits
        if (pwm_counter >= MaxDisplay::_pwm) {
            payload = color_mask
                | number_mux_map[MaxDisplay::_digits[current_digit]];

            //for (auto i : number_mux_map) {
            //    payload |= i;
            //}

        } else {
            payload = led_mux_map[current_digit] | dots_map[dots_state] | digit_mux_map[current_digit]
                    | color_mask
                    | number_mux_map[MaxDisplay::_digits[current_digit]];
        }

    }
}

ICACHE_RAM_ATTR
void
main_isr() {

        //tick ();

#ifdef USE_HW_CS
        // latch low
        digitalWrite (15, LOW);
#endif // USE_HW_CS

        while(SPI1CMD & SPIBUSY) {}

        setDataBits (24); //8 * sizeof(payload));
        SPI1W0 = payload;
        //SPI1W1 = payload >> 32;

        SPI1CMD |= SPIBUSY;

#ifndef USE_HW_CS
        while(SPI1CMD & SPIBUSY) {}
        // latchhigh
        digitalWrite (15, HIGH);
#endif // USE_HW_CS

}

void
MaxDisplay::init()
{
    SPI.begin ();
    SPI.setDataMode(SPI_MODE0);
#ifdef USE_HW_CS
    SPI.setHwCs(true);
#endif// USE_HW_CS
    SPI.setBitOrder(LSBFIRST);
    SPI.setFrequency(4000000);

    // tutaj
    setDataBits (24);

#ifndef USE_HW_CS
    pinMode (15, OUTPUT);
    digitalWrite (15, HIGH);
#endif // USE_HW_CS

    display_timer_divider = clockCyclesPerMicrosecond() / 16 * 80;

    timer1_isr_init ();
    timer1_attachInterrupt (main_isr);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
    timer1_write(display_timer_divider); //80us = 12.5kHz sampling freq

    pinMode (SHDN_PIN, OUTPUT);
    digitalWrite (SHDN_PIN, LOW);
}


void MaxDisplay::set_payload_str(const char *str) {
    memcpy (&payload, str, sizeof(payload));
}

void MaxDisplay::set_payload (MaxDisplay::payload_t payload_in) {
    payload = payload_in;
}

void MaxDisplay::setColor (uint8_t red, uint8_t green, uint8_t blue) {
    _red = red;
    _green = green;
    _blue = blue;
}

void MaxDisplay::setDigit (unsigned int digit, uint8_t value) {
    _digits[digit] = value;
}
