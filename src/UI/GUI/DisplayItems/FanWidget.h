#ifndef FAN_WIDGET_h
#define FAN_WIDGET_h

#include "DataWidget.h"
#include "Peripherals/FanController.h"

class FanWidget : public DataWidget {
    public:
    FanWidget(uint8_t x, uint8_t y, FanController*, GraphWidget* g = NULL);
    FanController* fans;

    void handleInput(void* menuManager) override;

};

#endif