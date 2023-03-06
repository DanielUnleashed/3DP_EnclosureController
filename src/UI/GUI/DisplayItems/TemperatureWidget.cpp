#include "TemperatureWidget.h"
#include "UI/MenuManager.h"

TemperatureWidget::TemperatureWidget(uint8_t x, uint8_t y, TemperatureSensor* tmp, GraphWidget* gr) : DisplayItem(x,y,3,2){
    this->tmp = tmp;
    this->graph = gr;
}

void TemperatureWidget::draw(void* menuManager){
    drawFilledRect(menuManager, 0, 0, 100, 100, 0x3949);
    drawRectangle(menuManager,  0, 0, 100, 100, 0x9b79);

    String tmpStr = String(tmp->getTemperature());
    uint8_t dotPosition = tmpStr.indexOf('.');
    tmpStr = tmpStr.substring(0, dotPosition+2);
    tmpStr += " C";

    drawCenteredText(menuManager, 50, 25, "Temperatura", 1, 0xFFFF);
    drawCenteredText(menuManager, 50, 60, tmpStr, 2, 0xFFFF);
}

void TemperatureWidget::handleInput(void* menuManager){
    MenuManager* m = (MenuManager*) menuManager;
    Serial.println(m->inputCode);
    if(m->inputCode == INPUT_BUTTON_CLICK){
        Display d = Display();
        d.addItem(graph);
        m->addDisplay(d);
    }
}