#include "LEDController.h"

LEDController::LEDController(uint8_t pinR, uint8_t pinG, uint8_t pinB){
    this->pinR = pinR;
    this->pinG = pinG;
    this->pinB = pinB;

    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void LEDController::setColor(uint8_t r, uint8_t g, uint8_t b){
    this->currentColor = {r,g,b};
}

bool LEDController::update(){
    bool ret = false;
    switch (selectedPattern) {
    case LED_CONSTANT:{
        break;
    }

    case LED_SINE:{
        double t = millis()*TWO_PI*speed/1000000;
        uint16_t k = 255*(sin(t)+1.0)/2.0;
        CHSV c = CHSV(k, 255,255);
        CRGB crgb;
        hsv2rgb_rainbow(c, crgb);
        currentColor = {crgb.r,crgb.g,crgb.b};
        //Serial.println("(" + String(t) + ") "+String(k) + "  -> " + String(currentColor.r) + " " + String(currentColor.g) + " " + String(currentColor.b));
        ret = true;
        break;
    }
    
    default:
        break;
    }

    outputColor();
    return ret;
}

void LEDController::outputColor(){
    analogWrite(pinR, currentColor.r);
    analogWrite(pinG, currentColor.g);
    analogWrite(pinB, currentColor.b);
}