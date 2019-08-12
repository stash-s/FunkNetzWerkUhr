

#include "spi_wrapper.h"

#include "clock_config.h"


#include "vfd_display.h"

uint8_t VfdDisplay::_digits[MAX_DIGITS];

uint32_t lcd_mux[] = {
     0x400,
     0x800,
     0x200,
     0x100
 };

uint32_t lcd_seg[] = {
    0b11111100, // 0
    0b01100000, // 1
    0b11011010, // 2
    0b11110010, // 3
    0b01100110, // 4
    0b10110110, // 5
    0b10111110, // 6
    0b11100000, // 7
    0b11111110, // 8
    0b11110110, // 9
};


static int display_timer_divider=0;
static int filament_divider = 250;
static uint8_t filament_pin;


ICACHE_RAM_ATTR
static void clock_display_callback () {

    SpiWrapper::setDataBits (20);

    static int digit=0;
    static int filament_counter=0;

    if (digit >= MAX_DIGITS) {
        digit = 0;
    }

    if (filament_counter >= filament_divider) {
        digitalWrite (filament_pin, ! digitalRead (filament_pin));
        filament_counter = 0;
    } else {
        ++filament_counter;
    }

    SpiWrapper::transmit ( lcd_mux[digit] | lcd_seg[VfdDisplay::getDigit(digit)], 20);

    ++digit;
}

VfdDisplay::VfdDisplay (const AppConfig & config)
    :Display (config)
{
    filament_pin = config.getFilamentPin ();
}

void
VfdDisplay::init () {

    Serial.println ("Initialining VFD timer.");

    SpiWrapper::init(20);

    display_timer_divider = (clockCyclesPerMicrosecond() / 16) * 40; // 40us = 25kHz sampling freq

    timer1_isr_init ();
    timer1_attachInterrupt (clock_display_callback);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
    timer1_write(display_timer_divider);


    pinMode (getConfig().getFilamentPin(), OUTPUT);
    digitalWrite (getConfig().getFilamentPin(), LOW);

    pinMode (getConfig().getShutdownPin(), OUTPUT);
    digitalWrite (getConfig().getShutdownPin(), LOW);
}

void
VfdDisplay::shutdown () {
    digitalWrite (getConfig().getShutdownPin(), HIGH);
}

void
VfdDisplay::setDigit (unsigned int digit, uint8_t value) {
    _digits[digit] = value;
}

void VfdDisplay::setBrightness (uint8_t brightness) 
{}

void VfdDisplay::startAnimation () {

}

void VfdDisplay::stopAnimation () {
    
}
