#ifndef FAN_CONTROLLER_h
#define FAN_CONTROLLER_h

#include "Arduino.h"

#include "TemperatureSensor.h"

#define FAN_LOW_TEMP 22.0
#define FAN_HIGH_TEMP 24.5

class FanController{
    public:
    FanController(uint8_t fanPin, TemperatureSensor* tmp);
    uint8_t fanPin;
    TemperatureSensor* tmp;

    bool fansEnabled = true;
    uint8_t output = 100;

    bool update();

};

#endif