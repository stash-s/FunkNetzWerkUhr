#ifndef __SPI_WRAPPER_H__
#define __SPI_WRAPPER_H__

#include <Arduino.h>

namespace SpiWrapper {

    ICACHE_RAM_ATTR
    inline void setDataBits(uint16_t bits) {
        const uint32_t mask = ~((SPIMMOSI << SPILMOSI) | (SPIMMISO << SPILMISO));
        bits--;
        SPI1U1 = ((SPI1U1 & mask) | ((bits << SPILMOSI) | (bits << SPILMISO)));
    }

    ICACHE_FLASH_ATTR
    void init(uint16_t dataBits);

    ICACHE_RAM_ATTR
    inline void transmit (uint32_t payload, uint16_t dataBits) {
        while(SPI1CMD & SPIBUSY) {}

        setDataBits (dataBits); //8 * sizeof(payload));
        SPI1W0 = payload;
        //SPI1W1 = payload >> 32;

        SPI1CMD |= SPIBUSY;
        //while(SPI1CMD & SPIBUSY) {}
    }
};

#endif // __SPI_WRAPPER_H__