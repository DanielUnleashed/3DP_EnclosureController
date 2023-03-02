#ifndef TEMPERATURE_WIDGET_h
#define TEMPERATURE_WIDGET_h

#include "UI/GUI/DisplayItem.h"
#include "Peripherals/TemperatureSensor.h"

class TemperatureWidget : public DisplayItem{

    public:
    TemperatureWidget(uint8_t x, uint8_t y, TemperatureSensor*);
    TemperatureSensor* tmp;

    void draw(void* menuManager) override;

};

#endif