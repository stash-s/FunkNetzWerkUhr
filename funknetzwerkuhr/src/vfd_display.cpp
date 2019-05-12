

#include "spi_wrapper.h"

#include "clock_config.h"


#include "vfd_display.h"



uint32_t lcd_mux[] = {
     0x2000,
     0x1000,
     0x4000,
     0x8000
 };

uint32_t lcd_seg[] = {
    0b11000000, // 0
    0b11111001, // 1
    0b10100100, // 2
    0b10110000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10010000  // 9
};


static int display_timer_divider=0;


ICACHE_RAM_ATTR
static void clock_display_callback () {

    SpiWrapper::setDataBits (20);

    static int digit=0;

    if (digit >= MAX_DIGITS) {
        digit = 0;
    }

    //SpiWrapper::transmit ( lcd_mux[digit] | lcd_seg[digit+1], 20);
    SpiWrapper::transmit ( 0xff00 | lcd_seg[4], 20);
}


VfdDisplay::VfdDisplay ()
{}



void
VfdDisplay::init () {

    Serial.println ("Initialining VFD timer.");

    SpiWrapper::init(20);

    display_timer_divider = (clockCyclesPerMicrosecond() / 16) * 20; // 40us = 25kHz sampling freq

    timer1_isr_init ();
    timer1_attachInterrupt (clock_display_callback);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
    timer1_write(display_timer_divider);


    pinMode (FILAMENT_PIN, OUTPUT);
    digitalWrite (FILAMENT_PIN, LOW);

    pinMode (SHDN_PIN, OUTPUT);
    digitalWrite (SHDN_PIN, LOW);
}

void
VfdDisplay::shutdown () {}

void
VfdDisplay::setDigit (unsigned int digit, uint8_t value) {

}

void VfdDisplay::setBrightness (uint8_t brightness) 
{}

void VfdDisplay::startAnimation () {

}

void VfdDisplay::stopAnimation () {
    
}
