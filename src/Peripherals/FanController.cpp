#include "FanController.h"

FanController::FanController(uint8_t fanPin, TemperatureSensor* tmp){
    this->fanPin = fanPin;
    this->tmp = tmp;

    pinMode(fanPin, OUTPUT);
    digitalWrite(fanPin, LOW);
}

bool FanController::update(){
  bool startingState = output>0;
  if(fansEnabled){
    bool out;
    if(output>0 && tmp->getTemperature() < FAN_LOW_TEMP){
      out = false;
    }else if(output==0 && tmp->getTemperature() > FAN_HIGH_TEMP){
      out = true;
    }else{
      out = output>0;
    }

    digitalWrite(fanPin, out);
    output = out ? 100 : 0;
  } // else...

  digitalWrite(fanPin, LOW);
  return digitalRead(fanPin)!=startingState;
}

