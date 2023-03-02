#ifndef ROTARYENCODER_h
#define ROTARYENCODER_h

#include "Arduino.h"

#define DEFAULT_ROTARY_DEBOUNCE 120

class RotEncoder{
    public:
        RotEncoder(uint8_t chA, uint8_t chB);

        int8_t getIncrement();

    private:
        uint32_t lastTimeChange = 0;
        uint8_t lastState = 0;
        int8_t increment = 0;
        uint8_t chA, chB; //Pins

        bool updateState();
};

#endif