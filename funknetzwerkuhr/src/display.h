#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Arduino.h>

class Display {
    public:
        virtual void init()=0;

        virtual void shutdown ()=0;
        virtual void setDigit (unsigned int digit, uint8_t value)=0;
        virtual void setColor (uint8_t red, uint8_t green, uint8_t blue, bool pulse=true);
        virtual void setBrightness (uint8_t brightness)=0;
};

#endif // __DISPLAY_H__