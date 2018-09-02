#ifndef __LIGHT_SENSOR_H__
#define __LIGHT_SENSOR_H__

#include <functional>

class LightSensor {

public:
    LightSensor ();
    void onReading (std::function<void(int)>);
    void onLevelSet (std::function<void(int)>);
    void handle ();

private:
    std::function<void(int)> _readingHandler;
    std::function<void(int)> _levelHandler;

};

#endif // __LIGHT_SENSOR_H__
