
#include <SPI.h>

#include "max_display.h"

#include <functional>

static std::function<void (void)> isr_callback;

inline void setDataBits(uint16_t bits) {
    const uint32_t mask = ~((SPIMMOSI << SPILMOSI) | (SPIMMISO << SPILMISO));
    bits--;
    SPI1U1 = ((SPI1U1 & mask) | ((bits << SPILMOSI) | (bits << SPILMISO)));
}


ICACHE_RAM_ATTR
static void isr_call () {
    isr_callback();
}

MaxDisplay::MaxDisplay()
{}

void
MaxDisplay::init()
{
    SPI.begin ();
    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(LSBFIRST);
    SPI.setFrequency(8000000);

    // tutaj

    pinMode (15, OUTPUT);
    digitalWrite (15, HIGH);


    isr_callback = [&](){main_isr();};
    timer1_isr_init ();
    timer1_attachInterrupt (isr_call);
    timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
    timer1_write(clockCyclesPerMicrosecond() / 16 * 80); //80us = 12.5kHz sampling freq
}

ICACHE_RAM_ATTR
void
MaxDisplay::main_isr() {
    // latch low
    digitalWrite (15, LOW);

    while(SPI1CMD & SPIBUSY) {}

    setDataBits (8 * sizeof(payload));
    SPI1W0 = payload;
    SPI1W1 = payload >> 32;

    SPI1CMD |= SPIBUSY;
    //while(SPI1CMD & SPIBUSY) {}

    // latchhigh
    digitalWrite (15, HIGH);

}

void MaxDisplay::set_payload_str(const char *str) {
    memcpy (&payload, str, sizeof(payload));

}
