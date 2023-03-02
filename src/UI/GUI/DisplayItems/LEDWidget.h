#ifndef LED_WIDGET_h
#define LED_WIDGET_h

#include "UI/GUI/DisplayItem.h"
#include "Peripherals/LEDController.h"

#define LED_FPS 2

#define LED_REFRESH_INTERVAL 1000/LED_FPS

class LEDWidget : public DisplayItem{
    public:
    LEDWidget(uint8_t x, uint8_t y, LEDController*);
    LEDController* led;

    void draw(void* menuManager) override;
};

#endif