#include "DisplayHeader.h"
#include "UI/MenuManager.h"

DisplayHeader::DisplayHeader(String headerName, uint8_t sizeX, uint8_t sizeY) : DisplayItem(0,0, sizeX, sizeY){
    this->headerName = headerName;
    this->drawItemSelectedSquare = false;
}

void DisplayHeader::draw(void* menuManager){
    drawFilledRect(menuManager, 0,0,100,100, 0x0f1938);
    drawRectangle(menuManager, 0,0,100,100, 0x263a75);

    if(isSelected){
        drawRoundFilledRectangle(menuManager, 80,0,20,100, 0x9f0cf4);
        drawRoundRectangle(menuManager, 80,0,20,100, 0xfcc40c);

        // Draw triangle
        const uint16_t trBase = 60;
        MenuManager* m = (MenuManager*) menuManager;
        Point initP = transformRelativePoint(m->getCurrentDisplay(), 85, 50);
        Point endP = transformRelativePoint(m->getCurrentDisplay(), 95, trBase);
        for(uint16_t x = initP.x; x <= endP.x; x++){
            uint16_t hLine = (x-initP.x)*endP.y/(endP.x-initP.x);
            m->tft->drawFastVLine(x, initP.y-hLine/2, hLine, createColor(0xc3, 0x96, 0xdd));
        }
    }
    drawText(menuManager, 10, 50, headerName, 2, 0xFFFFFF, TEXT_LC);
}

void DisplayHeader::handleInput(void* menuManager){
    MenuManager* m = (MenuManager*) menuManager;
    if(m->inputCode == INPUT_BUTTON_CLICK){
        m->returnToLastDisplay();
    }
}