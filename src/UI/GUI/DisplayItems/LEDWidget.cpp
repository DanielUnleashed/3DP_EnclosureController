#include "LEDWidget.h"

LEDWidget::LEDWidget(uint8_t x, uint8_t y, LEDController* led) : DisplayItem(x,y,3,2){
    this->led = led;
}

void LEDWidget::draw(void* menuManager){
    static uint32_t lastDrawTime = 0;
    uint32_t now = millis();

    if(now - lastDrawTime > LED_REFRESH_INTERVAL){
        lastDrawTime = now;
        uint16_t c = createColor(led->currentColor.r, led->currentColor.g, led->currentColor.b);
        drawFilledRect(menuManager, 0, 0, 100, 100, c);
        drawRectangle(menuManager,  0, 0, 100, 100, 0x9b79);

        drawCenteredText(menuManager, 50, 25, "LED", 1, 0xFFFF);
        drawCenteredText(menuManager, 50, 60, String(led->brightness) + " %", 2, 0xFFFF);        
    }

}