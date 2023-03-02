#include "FanController.h"

FanController::FanController(uint8_t fanPin, TemperatureSensor* tmp){
    this->fanPin = fanPin;
    this->tmp = tmp;

    pinMode(fanPin, OUTPUT);
    digitalWrite(fanPin, LOW);
}

bool FanController::update(){
  bool out = tmp->getHumidity() > 50 || tmp->getTemperature() > 25;
  bool statusChanged = out!=fanOn;
  digitalWrite(fanPin, out);
  fanOn = out;
  if(fanOn){
    output = 100;
  }else{
    output = 0;
  }
  return statusChanged;
}

