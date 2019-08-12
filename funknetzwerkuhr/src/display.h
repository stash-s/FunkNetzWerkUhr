#pragma once

#include <Arduino.h>
#include "appconfig.h"

class Display {
    public:
        Display (const AppConfig & config);

        virtual void init()=0;

        virtual void shutdown ()=0;
        virtual void setDigit (unsigned int digit, uint8_t value)=0;
        virtual void setColor (uint8_t red, uint8_t green, uint8_t blue);
        virtual void startAnimation ();
        virtual void stopAnimation ();
        virtual void setBrightness (uint8_t brightness)=0;

        const AppConfig & getConfig () const;

    private:
        const AppConfig & _config;
};

inline
const AppConfig & Display::getConfig () const {
    return _config;
}
