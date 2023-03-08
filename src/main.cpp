#include <Arduino.h>
#include "Peripherals/TemperatureSensor.h"
#include "Peripherals/FanController.h"
#include "Peripherals/LEDController.h"

#include "UI/MenuManager.h"
#include "UI/GUI/DisplayItems/DataWidget.h"
#include "UI/GUI/DisplayItems/LEDWidget.h"
#include "UI/GUI/DisplayItems/GraphWidget.h"

#define DHT11_PIN PD2
#define TMP36_PIN A7
#define FAN_PIN 3

// TFT screen pinout
#define CS_PIN 10
#define A0_PIN PD7 //aka. DC pin
#define RS_PIN 8

#define RED_PIN   PB1
#define GREEN_PIN PD6 
#define BLUE_PIN  PD5

TemperatureSensor tmp(DHT11_PIN, TMP36_PIN);
FanController fans(FAN_PIN, &tmp);
LEDController leds(RED_PIN, GREEN_PIN, BLUE_PIN);

GraphWidget tempGraph(0,1,6,4);
GraphWidget humidityGraph(0,1,6,4);

MenuManager menu;
DataWidget tmpWidget("Temperatura", 0,0, &tempGraph);
DataWidget hmWidget("Humedad", 3,0, &humidityGraph);
DataWidget fanWidget("Ventiladores", 0,2);
LEDWidget ledWidget(3,2, &leds);

void setup(){
  Serial.begin(9600);

  menu.init(CS_PIN, A0_PIN, RS_PIN);
  Display mainD = Display();
  mainD.addItem(&tmpWidget);
  mainD.addItem(&hmWidget);
  mainD.addItem(&fanWidget);
  mainD.addItem(&ledWidget);
  
  menu.addDisplay(mainD);

  Serial.println("Start");
}

long lastTimer = 0;

void loop(){
  if(leds.update()){
    ledWidget.redraw();
  }

  tmp.update();
  if(tmp.dataReady()){
    tmp.printValues();
    if(fans.update()){
      fanWidget.setData(fans.output);
    }

    tempGraph.addPoint(tmp.getTemperature());
    humidityGraph.addPoint(tmp.getHumidity());

    tmpWidget.setData(tmp.getTemperature());
    hmWidget.setData(tmp.getHumidity());
  }
  menu.update();
  delay(1);
}