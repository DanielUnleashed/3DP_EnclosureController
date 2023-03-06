#ifndef TEMPERATURE_WIDGET_h
#define TEMPERATURE_WIDGET_h

#include "UI/GUI/DisplayItem.h"
#include "Peripherals/TemperatureSensor.h"
#include "UI/GUI/DisplayItems/GraphWidget.h"

class TemperatureWidget : public DisplayItem{

    public:
    TemperatureWidget(uint8_t x, uint8_t y, TemperatureSensor*, GraphWidget*);
    TemperatureSensor* tmp;
    GraphWidget* graph;

    void draw(void* menuManager) override;
    void handleInput(void* menuManager);

};

#endif