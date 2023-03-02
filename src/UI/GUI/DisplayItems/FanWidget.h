#ifndef FAN_WIDGET_h
#define FAN_WIDGET_h

#include "Peripherals/FanController.h"
#include "UI/GUI/DisplayItem.h"

class FanWidget : public DisplayItem{
    public:
    FanWidget(uint8_t x, uint8_t y, FanController*);
    FanController* fan;

    void draw(void* menuManager) override;
};
#endif