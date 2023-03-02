#ifndef FAN_CONTROLLER_h
#define FAN_CONTROLLER_h

#include "Arduino.h"

#include "TemperatureSensor.h"

class FanController{
    public:
    FanController(uint8_t fanPin, TemperatureSensor* tmp);
    uint8_t fanPin;
    TemperatureSensor* tmp;

    bool fanOn = false;
    uint8_t output = 100;

    bool update();

};

#endif