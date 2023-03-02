#ifndef HUMIDITY_WIDGET_h
#define HUMIDITY_WIDGET_h

#include "UI/GUI/DisplayItem.h"
#include "Peripherals/TemperatureSensor.h"

class HumidityWidget : public DisplayItem{

    public:
    HumidityWidget(uint8_t x, uint8_t y, TemperatureSensor*);
    TemperatureSensor* tmp;

    void draw(void* menuManager) override;

};

#endif