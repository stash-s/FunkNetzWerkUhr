
#include <functional>

#include <SPI.h>

#include "ausf_a_display.h"
#include "clock_config.h"

static uint32_t payload = 0;

bool AusfADisplay::_animate = false;

uint8_t AusfADisplay::_digits[MAX_DIGITS];
uint8_t AusfADisplay::_pwm = PWM_INIT;
uint8_t AusfADisplay::_slot_effect[MAX_DIGITS] = {0, 0, 0, 0};

ICACHE_RAM_ATTR
static int display_timer_divider = 0;

ICACHE_RAM_ATTR
static int filament_timer_divider = 0;

uint32_t lcd_mux[] = {0x400, 0x800, 0x200, 0x100};

static uint32_t lcd_seg_mask[] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110  // 9
};

static uint32_t lcd_dot_mask[] = {0x0000, 0x0001};

ICACHE_RAM_ATTR
inline void setDataBits(uint16_t bits) {
    const uint32_t mask = ~((SPIMMOSI << SPILMOSI) | (SPIMMISO << SPILMISO));
    bits--;
    SPI1U1 = ((SPI1U1 & mask) | ((bits << SPILMOSI) | (bits << SPILMISO)));
}

AusfADisplay::AusfADisplay() {}

void AusfADisplay::setBrightness(uint8_t brightness) { _pwm = brightness; }

ICACHE_RAM_ATTR
uint8_t ausf_a_get_digit(unsigned int digit) {

    static uint8_t slot_number[] = {4, 2, 6, 9};
    static int counter = 0;

    ++counter;
    if (counter >= display_timer_divider * 16 * 8) {
        counter = 0;

        for (int i = 0; i < MAX_DIGITS; ++i) {
            if (AusfADisplay::_slot_effect[i] > 0) {
                if (AusfADisplay::_animate &&
                    (AusfADisplay::_digits[i] == slot_number[i])) {
                    --AusfADisplay::_slot_effect[i];
                }
            }

            ++slot_number[i];
            if (slot_number[i] > 9) {
                slot_number[i] = 0;
            }
        }
    }

    if (AusfADisplay::_slot_effect[digit] > 0) {
        return slot_number[digit];
    } else {
        return AusfADisplay::_digits[digit];
    }
}

ICACHE_RAM_ATTR
void ausf_a_tick(/* arguments */) {
    static int current_digit = 0;
    static int seconds_counter = 0;
    static int pwm_counter = 0;

    static int filament_clock = 0;
    static int filament_state = 0;

    if (++filament_clock >= filament_timer_divider) {
        filament_clock = 0;

        filament_state = filament_state ? 0 : 1;
        digitalWrite(FILAMENT_PIN, filament_state);
    }

    ++pwm_counter;
    if (pwm_counter >= PWM_MAX) {
        pwm_counter = 0;

        ++current_digit;
        if (current_digit >= MAX_DIGITS) {
            current_digit = 0;
        }
    }

    static int dots_state = 0;
    static int dot_digit  = 0;
    ++seconds_counter;
    if (seconds_counter >= (display_timer_divider * 16 * 16)) {
        seconds_counter = 0;
        dots_state = dots_state ? 0 : 1;
        if (dots_state) {
            if (++dot_digit >= MAX_DIGITS) {
                dot_digit = 0;
            }
        }
    }
    uint32_t dot_mask = (current_digit == dot_digit) ? lcd_dot_mask[dots_state] : 0;

    uint32_t number_mask = lcd_seg_mask[ausf_a_get_digit(current_digit)];


    // if pwm counter >= pwm, blank digits
    if (pwm_counter >= AusfADisplay::_pwm) {
        payload = 0; // number_mask;
    } else {
        payload = dot_mask | lcd_mux[current_digit] | number_mask;
    }
}

ICACHE_RAM_ATTR
static void isr_call() {

    ausf_a_tick();

    while (SPI1CMD & SPIBUSY) {
    }

    setDataBits(20);
    //    payload = lcd_mux[2] | 0b10000000;
    SPI1W0 = payload;
    SPI1CMD |= SPIBUSY;
}

void AusfADisplay::init() {
    SPI.begin();
    SPI.setDataMode(SPI_MODE0);
    SPI.setHwCs(true);
    SPI.setBitOrder(LSBFIRST);
    SPI.setFrequency(8000000);

    // tutaj
    setDataBits (20);

    display_timer_divider =
        (clockCyclesPerMicrosecond() / 16) * 20; // 20us = 50kHz sampling freq

    filament_timer_divider = 500; // 100Hz

    timer1_isr_init();
    timer1_attachInterrupt(isr_call);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
    timer1_write(display_timer_divider);

    pinMode(FILAMENT_PIN, OUTPUT);
    pinMode(SHDN_PIN, OUTPUT);
    digitalWrite(SHDN_PIN, LOW);

#ifdef DEBUG
    Serial.println("Initialized display");
#endif
}

void AusfADisplay::shutdown() { digitalWrite(SHDN_PIN, HIGH); }

void AusfADisplay::setDigit(unsigned int digit, uint8_t value) {
    _digits[digit] = value;
}

void AusfADisplay::setColor(uint8_t red, uint8_t green, uint8_t blue,
                            bool pulse_colors) {
    _animate = pulse_colors;

    if (!_animate) {
        uint8_t spins = 5;
        for (auto &i : _slot_effect) {
            i = spins;
            spins -= 1;
        }
    }
}