#pragma once

#include <functional>

class Delay {
    public:
        void delay(std::function<void()> action, unsigned int delay_time = 1000);
        void handle();

    private:
        std::function<void()> _action;
        unsigned int _due_time;
};