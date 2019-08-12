
#include "clock_config.h"
#include "spi_wrapper.h"
#include "nixie_display.h"

#include <functional>

using namespace SpiWrapper;

static NixieDisplay::payload_t payload=0;
static uint8_t  digitsCount;

bool NixieDisplay::_pulse_colors = false;

uint8_t NixieDisplay::_red=0;
uint8_t NixieDisplay::_green=0;
uint8_t NixieDisplay::_blue=0;
uint8_t NixieDisplay::_digits[MAX_DIGITS];
uint8_t NixieDisplay::_pwm=PWM_INIT;
uint8_t NixieDisplay::_slot_effect[MAX_DIGITS]={0,0,0,0};

static int display_timer_divider=0;

static NixieDisplay::payload_t *led_mux_map;
static NixieDisplay::payload_t *color_map;
static NixieDisplay::payload_t *dots_map;
static NixieDisplay::payload_t *digit_mux_map;
static NixieDisplay::payload_t *number_mux_map;

static NixieDisplay::payload_t ausf_a_led_mux_map[] = {
    0b000100000000000000000000, // digit 1
    0b001000000000000000000000, // digit 2
    0b010000000000000000000000, // digit 3
    0b100000000000000000000000, // nope
};

static NixieDisplay::payload_t ausf_a_color_map[] = {
    0b000011000000000000000000, // red
    0b000010100000000000000000, // green
    0b000001100000000000000000, // blue
    0b000010100000000000000000, // green
    0b000011100000000000000000, // blank all
};


static NixieDisplay::payload_t ausf_a_dots_map[] = {
    0b000000000000000000000000, // dots off
    0b000000011000000000000000  // dots on
};


static NixieDisplay::payload_t ausf_a_digit_mux_map[] = {
    0b0001, // digit 1
    0b0010, // digit 2
    0b0100, // digit 3
    0b1000, // digit 4
};


static NixieDisplay::payload_t ausf_a_number_mux_map[] = {
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

static NixieDisplay::payload_t ausf_c_led_mux_map[] = {
    0b000100000000000000000000, // digit 1
    0b000000000010000000000000, // digit 2
    0b000000000000000001000000, // digit 3
    0b000000000000000000000001, // nope
    //   |   |   |   |   |   |
};

static NixieDisplay::payload_t ausf_c_color_map[] = {
    0b001000000000000000000010, // green
    0b000000000001000000000010, // red
    0b001000000001000000000000, // blue
    0b001000000001000000000010, // blank all
    
    0b001000000000000000000010, // green
    //   |   |   |   |   |   |
};


static NixieDisplay::payload_t ausf_c_dots_map[] = {
    0,
    0b000000000000001100000000, // dots off
    //0 //0b000000011000000000000000  // dots on
};


static NixieDisplay::payload_t ausf_c_digit_mux_map[] = {
    //   |   |   |   |   |   |
    0b100000000000000000000000, //0b0001, // digit 1
    0b000000001000000000000000, //0b0010, // digit 2
    0b000000000000010000000000, //0b0100, // digit 3
    0b000000000000000000010000, //0b1000, // digit 4
};

static NixieDisplay::payload_t ausf_c_number_mux_map[] = {
    //   |   |   |   |   |   |
    0b000001000000000000000000,// 0b1000000000000, // number 0
    0b000000000000000000100000,// 0b1000000000, // number 1
    0b000000000000000000001000,// 0b100000000, // number 2
    0b000000000000000000000100,// 0b10000000, // number 3
    0b000000010000000000000000,// 0b10000, // number 4
    0b010000000000000000000000,// 0b100000, // number 5
    0b000000000100000000000000,// 0b100000000000000, // number 6
    //   |   |   |   |   |   |
    0b000000000000000010000000,// 0b100000000000, // number 7
    0b000010000000000000000000,// 0b1000000, // number 8
    0b000000000000100000000000,// 0b10000000000000, // number 9
    0b000000100000000000000000,//    0b10000000000, // dot
};

NixieDisplay::NixieDisplay(const AppConfig & config)
    :Display (config)
{}

void  NixieDisplay::setBrightness (uint8_t brightness) {
    _pwm = brightness;
}

ICACHE_RAM_ATTR
uint8_t get_digit (unsigned int digit) {

    static uint8_t slot_number[] = {4,2,6,9};
    static int counter=0;

    ++counter;
    if (counter >= display_timer_divider * 16 * 4) {
        counter = 0;

        for (int i=0; i < MAX_DIGITS; ++i) {
            if (NixieDisplay::_slot_effect[i] > 0) {
                if (NixieDisplay::_pulse_colors && (NixieDisplay::_digits[i] == slot_number[i])) {
                    -- NixieDisplay::_slot_effect[i];
                }
            }

            ++slot_number[i];
            if (slot_number[i] > 9) {
                slot_number[i] = 0;
            }
        }
    }

    if (NixieDisplay::_slot_effect[digit] > 0) {
        return slot_number[digit];
    } else {
        return NixieDisplay::_digits[digit];
    }
}

ICACHE_RAM_ATTR
void tick (/* arguments */) {
    static int current_digit=0;
    static int seconds_counter=0;
    static int pwm_counter=0;
    static uint8_t color_counter=0;

    ++color_counter;

    ++pwm_counter;
    if (pwm_counter >= PWM_MAX) {
        pwm_counter = 0;

        ++current_digit;
        if ( current_digit >= MAX_DIGITS ) {
             current_digit = 0;
        }

    }

        //NixieDisplay::payload_t anodes=0;

        static int dots_state = 0;
        ++ seconds_counter;
        if ( seconds_counter >= (display_timer_divider * 16 * 16) ) {
            seconds_counter = 0;
            dots_state = dots_state ? 0 : 1;
            if (dots_state && NixieDisplay::_pulse_colors) {
                NixieDisplay::_red  += 7;
                NixieDisplay::_blue += 5;
                NixieDisplay::_green -= 1;
            }

        }

        uint32_t color_mask = color_map[3];
        uint32_t number_mask = number_mux_map[get_digit(current_digit)];

        // if pwm counter >= pwm, blank digits
        if (pwm_counter >= NixieDisplay::_pwm) {
            payload = color_mask | number_mask;

        } else {

            if (NixieDisplay::_red   > color_counter) color_mask &= color_map[0];
            if (NixieDisplay::_green > color_counter) color_mask &= color_map[1];
            if (NixieDisplay::_blue  > color_counter) color_mask &= color_map[2];

            #ifdef FULL_COLOR
                for (int i=0; i < digitsCount; ++i) {
                    color_mask |= led_mux_map[i];
                }
            #else
                color_mask |= led_mux_map[current_digit];
            #endif

            payload = dots_map[dots_state] | digit_mux_map[current_digit]
                    | color_mask | number_mask;
        }
}

ICACHE_RAM_ATTR
static void isr_call () {

    tick();

    SpiWrapper::transmit (payload, 24);

}

void
NixieDisplay::init()
{
    Serial.println ("Nixie display init()");

    switch (getConfig().getHardwareVariant()) {
        case NIXIE_AUSF_A:
            led_mux_map = ausf_a_led_mux_map;
            color_map = ausf_a_color_map;
            dots_map = ausf_a_dots_map;
            digit_mux_map = ausf_a_digit_mux_map;
            number_mux_map = ausf_a_number_mux_map;
            break;
        
        case NIXIE_AUSF_C:
        case NIXIE_AUSF_D:
            led_mux_map = ausf_c_led_mux_map;
            color_map = ausf_c_color_map;
            dots_map = ausf_c_dots_map;
            digit_mux_map = ausf_c_digit_mux_map;
            number_mux_map = ausf_c_number_mux_map;
            break;

        default:
            Serial.println ("Unsupported Nixie hardware, bailing out with AUSF_A defaults.");

            break;
    }

    digitsCount = getConfig ().getDigitsCount ();

    SpiWrapper::init(24);

    display_timer_divider = (clockCyclesPerMicrosecond() / 16) * 20; // 40us = 25kHz sampling freq

    timer1_isr_init ();
    timer1_attachInterrupt (isr_call);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
    timer1_write(display_timer_divider);

    pinMode (getConfig().getShutdownPin(), OUTPUT);
    digitalWrite (getConfig().getShutdownPin(), LOW);
}


void NixieDisplay::shutdown () {
    digitalWrite (getConfig().getShutdownPin(), HIGH);
}

void NixieDisplay::setDigit (unsigned int digit, uint8_t value) {
    _digits[digit] = value;
}

void NixieDisplay::setColor (uint8_t red, uint8_t green, uint8_t blue) {
    _red = red;
    _green = green;
    _blue = blue;
}

void NixieDisplay::startAnimation () {
    _pulse_colors = false;

    int spins=5;

    for (auto &i : _slot_effect) { 
        i = spins;
        spins -= 1;
    }
}

void NixieDisplay::stopAnimation () {
    _pulse_colors = true;
}
