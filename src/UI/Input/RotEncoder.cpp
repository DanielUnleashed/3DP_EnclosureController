#include "RotEncoder.h"

const int8_t ROTATION_DIRECTION[16] = {
            0,  -1,   1,  0,
            1,   0,   0, -1,
           -1,   0,   0,  1,
            0,   1,  -1,  0};

RotEncoder::RotEncoder(uint8_t a, uint8_t b){
    this->chA = a;
    this->chB = b;
    pinMode(chA, INPUT_PULLUP);
    pinMode(chB, INPUT_PULLUP);
    lastState = digitalRead(chA) | (digitalRead(chB) << 1);
}

bool RotEncoder::updateState(){
    bool ret = false;
    uint8_t currentPinState = digitalRead(chA) | (digitalRead(chB) << 1);
    uint32_t currentTime = millis();
    if(currentPinState != lastState){
        if((currentTime - lastTimeChange) > DEFAULT_ROTARY_DEBOUNCE){
            lastTimeChange = currentTime;
            increment = ROTATION_DIRECTION[currentPinState | (lastState << 2)];
            ret =  true;
        }
        lastState = currentPinState;
    }
    return ret;
}

int8_t RotEncoder::getIncrement(){
    if(!updateState()) return 0;
    return increment;
}