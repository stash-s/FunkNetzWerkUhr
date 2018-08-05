#ifndef __MAX_DISPLAY_H__
#define __MAX_DISPLAY_H__

#include <Arduino.h>

class MaxDisplay {

private:
    uint64_t payload;

public:

    MaxDisplay ();
    void init();
    void set_payload_str (const char *str);

private:

    ICACHE_RAM_ATTR
    void main_isr();

};

#endif //  __MAX_DISPLAY_H__
