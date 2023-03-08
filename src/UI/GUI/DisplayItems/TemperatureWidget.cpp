#include "TemperatureWidget.h"
#include "UI/MenuManager.h"

TemperatureWidget::TemperatureWidget(uint8_t x, uint8_t y, TemperatureSensor* tmp, GraphWidget* gr) : DisplayItem(x,y,3,2){
    this->tmp = tmp;
    this->graph = gr;
}

void TemperatureWidget::draw(void* menuManager){
    drawFilledRect(menuManager, 0, 0, 100, 100, 0x263a75);
    drawRectangle(menuManager,  0, 0, 100, 100, 0x4c6ed3);

    String tmpStr = String(tmp->getTemperature());
    uint8_t dotPosition = tmpStr.indexOf('.');
    tmpStr = tmpStr.substring(0, dotPosition+2);
    tmpStr += " C";

    drawText(menuManager, 50, 25, "Temperatura", 1, 0xFFFFFF, TEXT_CC);
    drawText(menuManager, 50, 60, tmpStr, 2, 0xFFFFFF, TEXT_CC);
}

void TemperatureWidget::handleInput(void* menuManager){
    MenuManager* m = (MenuManager*) menuManager;
    if(m->inputCode == INPUT_BUTTON_CLICK){
        HeadedDisplay d = HeadedDisplay("Temperatura", 6,5);
        d.addItem(graph);
        m->addDisplay(d);
    }
}