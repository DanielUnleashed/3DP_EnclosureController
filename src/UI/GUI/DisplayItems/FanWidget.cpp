#include "FanWidget.h"

FanWidget::FanWidget(uint8_t x, uint8_t y, FanController* fan) : DisplayItem(x,y,3,2){
    this->fan = fan;
}

void FanWidget::draw(void* menuManager){
    drawFilledRect(menuManager, 0, 0, 100, 100, 0x263a75);
    drawRectangle(menuManager,  0, 0, 100, 100, 0x4c6ed3);

    String outputStr = String(fan->output);
    uint8_t dotPosition = outputStr.indexOf('.');
    outputStr = outputStr.substring(0, dotPosition+2);
    outputStr += " %";

    drawText(menuManager, 50, 25, "Ventiladores", 1, 0xFFFFFF, TEXT_CC);
    drawText(menuManager, 50, 60, outputStr, 2, 0xFFFFFF, TEXT_CC);
}