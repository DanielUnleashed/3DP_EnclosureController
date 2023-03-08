#ifndef ROTARYENCODER_h
#define ROTARYENCODER_h

#include "Arduino.h"

#define DEFAULT_ROTARY_DEBOUNCE 120

class RotEncoder{
    public:
        RotEncoder(uint8_t chA, uint8_t chB);

        int8_t getIncrement();
        // Return true if there's any input
        bool pollState();

    private:
        uint8_t prevNextCode = 0;
        uint16_t store = 0;
        
        int8_t increment = 0;
        uint8_t chA, chB; //Pins

        bool updateState();
        bool rotEncoderState = false;
};

#endif