#include "DataWidget.h"
#include "UI/MenuManager.h"

DataWidget::DataWidget(String name, uint8_t x, uint8_t y, GraphWidget* gr, char units) : DisplayItem(x,y,3,2){
    this->name = name;
    this->units = units;
    this->graph = gr;
}

void DataWidget::setData(double data){
    if(this->data == data) return;
    this->data = data;
    redraw();
}

void DataWidget::draw(void* menuManager){
    drawFilledRect(menuManager, 0, 0, 100, 100, 0x263a75);
    drawRectangle(menuManager,  0, 0, 100, 100, 0x4c6ed3);

    String dataStr = String(data);
    uint8_t dotPosition = dataStr.indexOf('.');
    dataStr = dataStr.substring(0, dotPosition+2);
    if(units != 0){
        dataStr += " ";
        dataStr += String(units);
    }

    drawText(menuManager, 50, 25, name, 1, 0xFFFFFF, TEXT_CC);
    drawText(menuManager, 50, 60, dataStr, 2, 0xFFFFFF, TEXT_CC);
}

void DataWidget::handleInput(void* menuManager){
    MenuManager* m = (MenuManager*) menuManager;
    if(m->inputCode == INPUT_BUTTON_CLICK && graph!=NULL){
        HeadedDisplay d(name, 6,5);
        d.addItem(graph);
        m->addDisplay(d);
    }
}