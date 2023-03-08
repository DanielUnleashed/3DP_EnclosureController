#include "LEDWidget.h"

LEDWidget::LEDWidget(uint8_t x, uint8_t y, LEDController* led) : DisplayItem(x,y,3,2){
    this->led = led;
}

void LEDWidget::draw(void* menuManager){
    static uint32_t lastDrawTime = 0;
    uint32_t now = millis();

    if(now - lastDrawTime > LED_REFRESH_INTERVAL){
        lastDrawTime = now;

        uint32_t r = led->currentColor.r;
        uint32_t g = led->currentColor.g;
        uint32_t b = led->currentColor.b;
        uint32_t c = (r<<16) | (g<<8) | b;
        drawFilledRect(menuManager, 0, 0, 100, 100, c);
        drawRectangle(menuManager,  0, 0, 100, 100, 0x4c6ed3);

        drawText(menuManager, 50, 25, "LED", 1, 0xFFFFFF, TEXT_CC);
        drawText(menuManager, 50, 60, String(led->brightness) + " %", 2, 0xFFFFFF, TEXT_CC);        
    }

}