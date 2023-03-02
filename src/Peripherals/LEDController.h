#ifndef LED_CONTROLLER_h
#define LED_CONTROLLER_h

#include "Arduino.h"
#include <hsv2rgb.h>

typedef struct {
    uint8_t r,g,b;
}Color;

class LEDController{
    public:
    LEDController(uint8_t pinR, uint8_t pinG, uint8_t pinB);
    uint8_t pinR, pinG, pinB;

    Color currentColor;
    uint8_t brightness = 100;

    // Pattern
    #define LED_CONSTANT 0
    #define LED_SINE 1
    uint8_t selectedPattern = LED_SINE;
    uint8_t speed = 10;
    
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    // Returns true if the color has been updated
    bool update();
    
    private:
    void outputColor();

};

#endif