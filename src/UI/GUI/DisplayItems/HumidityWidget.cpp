#include "HumidityWidget.h"

HumidityWidget::HumidityWidget(uint8_t x, uint8_t y, TemperatureSensor* tmp) : DisplayItem(x,y,3,2){
    this->tmp = tmp;
}

void HumidityWidget::draw(void* menuManager){
    drawFilledRect(menuManager, 0, 0, 100, 100, 0x263a75);
    drawRectangle(menuManager,  0, 0, 100, 100, 0x4c6ed3);

    String hmdStr = String(tmp->getHumidity());
    uint8_t dotPosition = hmdStr.indexOf('.');
    hmdStr = hmdStr.substring(0, dotPosition);
    hmdStr += " %";

    drawText(menuManager, 50, 25, "Humedad", 1, 0xFFFFFF, TEXT_CC);
    drawText(menuManager, 50, 60, hmdStr, 2, 0xFFFFFF, TEXT_CC);
}