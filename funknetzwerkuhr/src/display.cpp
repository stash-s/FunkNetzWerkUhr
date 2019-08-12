#include "display.h"

Display::Display (const AppConfig & config)
    :_config (config)
{}

void Display::setColor (uint8_t, uint8_t, uint8_t) {
    // no-op for timepieces that do not support colors
}

ICACHE_RAM_ATTR
void Display::startAnimation () {

}

ICACHE_RAM_ATTR
void Display::stopAnimation () {

}