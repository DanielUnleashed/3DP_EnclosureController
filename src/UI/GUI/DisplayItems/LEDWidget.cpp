#include "LEDWidget.h"
#include "UI/MenuManager.h"

LEDWidget::LEDWidget(uint8_t x, uint8_t y, LEDController* led) : DisplayItem(x,y,3,2){
    this->led = led;
}

void LEDWidget::draw(void* menuManager){
    static uint32_t lastDrawTime = 0;
    uint32_t now = millis();

    if(now - lastDrawTime > LED_REFRESH_INTERVAL){
        lastDrawTime = now;

        uint32_t c;
        if(this->led->ledsOn){
            uint32_t r = led->currentColor.r;
            uint32_t g = led->currentColor.g;
            uint32_t b = led->currentColor.b;
            c = (r<<16) | (g<<8) | b;
        }else{
            c = 0x5f5c60; // Gray color
        }
        drawFilledRect(menuManager, 0, 0, 100, 100, c);
        drawRectangle(menuManager,  0, 0, 100, 100, 0x4c6ed3);

        drawText(menuManager, 50, 25, "LED", 1, 0xFFFFFF, TEXT_CC);
        if(this->led->ledsOn){
            drawText(menuManager, 50, 60, String(led->brightness) + " %", 2, 0xFFFFFF, TEXT_CC);  
        }else{
            drawText(menuManager, 50, 60, "OFF", 2, 0xFFFFFF, TEXT_CC);  
        }
              
    }
}

void LEDWidget::handleInput(void* menuManager){
    MenuManager* m = (MenuManager*) menuManager;
    if(m->inputCode == INPUT_BUTTON_CLICK){
        this->led->switchState(!this->led->ledsOn);
    }
}