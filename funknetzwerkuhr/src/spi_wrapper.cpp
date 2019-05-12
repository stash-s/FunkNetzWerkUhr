#include "spi_wrapper.h"

#include <SPI.h>

ICACHE_FLASH_ATTR
void SpiWrapper::init (uint16_t dataBits) {
    SPI.begin ();
    SPI.setDataMode(SPI_MODE0);
    SPI.setHwCs(true);
    SPI.setBitOrder(LSBFIRST);
    SPI.setFrequency(4000000);

    // tutaj
    setDataBits (dataBits);
}
