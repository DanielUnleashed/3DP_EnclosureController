#include "FanWidget.h"
#include "UI/MenuManager.h"

FanWidget::FanWidget(uint8_t x, uint8_t y, FanController* fan, GraphWidget* g) : DataWidget("Ventiladores", x,y,g,0){
    this->fans = fan;
}

void FanWidget::handleInput(void* menuManager){
    MenuManager* m = (MenuManager*) menuManager;
    if(m->inputCode == INPUT_BUTTON_CLICK){
        fans->fansEnabled = !fans->fansEnabled;
    }
}