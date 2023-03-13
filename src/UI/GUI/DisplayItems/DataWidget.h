#ifndef DATA_WIDGET_h
#define DATA_WIDGET_h

#include "UI/GUI/DisplayItem.h"
#include "Peripherals/TemperatureSensor.h"
#include "UI/GUI/DisplayItems/GraphWidget.h"

class DataWidget : public DisplayItem{

    public:
    DataWidget(String name, uint8_t x, uint8_t y, GraphWidget* g = NULL, char units = 0);
    GraphWidget* graph;

    String name;
    char units;
    double data = 0;

    void setData(double data);

    void draw(void* menuManager) override;
    void handleInput(void* menuManager);

};

#endif