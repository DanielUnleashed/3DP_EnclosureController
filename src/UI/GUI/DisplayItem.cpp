#include "DisplayItem.h"
#include "UI/MenuManager.h"
#include "Display.h"

DisplayItem::DisplayItem(uint8_t x, uint8_t y, uint8_t sX, uint8_t sY){
    static uint16_t createdItemCount = 0;

    this->x = x;
    this->y = y;
    this->sizeX = sX;
    this->sizeY = sY;
    this->itemID = createdItemCount++;
}

Point DisplayItem::transformRelativePoint(void* display, uint8_t pX, uint8_t pY){
    Display* currentDisplay = ((Display*) display);
    
    uint16_t oX = currentDisplay->x + currentDisplay->padLeft + x*currentDisplay->tileSize;
    uint16_t oY = currentDisplay->y + currentDisplay->padTop + y*currentDisplay->tileSize;
    // Serial.println("oX: " + String(oX) + " oY: " + String(oY));

    Point ret;
    ret.x = oX + sizeX*currentDisplay->tileSize*pX/100;
    ret.y = oY + sizeY*currentDisplay->tileSize*pY/100;
    // Serial.println("X: " + String(ret.x) + " Y: " + String(ret.y));
    return ret;
}

void DisplayItem::redraw(){
    this->needsUpdate = true;
}

uint16_t DisplayItem::createColor(uint8_t r, uint8_t g, uint8_t b){
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

// ***** DRAW FUNCTIONS *****
void DisplayItem::drawRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t lx = sizeX*m->getCurrentDisplay()->tileSize*sX/100;
    uint16_t ly = sizeY*m->getCurrentDisplay()->tileSize*sY/100;

    m->tft->drawRect(transP.x, transP.y, lx, ly, color);
}

void DisplayItem::drawRoundRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t lx = sizeX*m->getCurrentDisplay()->tileSize*sX/100;
    uint16_t ly = sizeY*m->getCurrentDisplay()->tileSize*sY/100;

    m->tft->drawRoundRect(transP.x, transP.y, lx, ly, 4, color);
}

void DisplayItem::drawRectangleByCenter(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point centerP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    Point transP = {centerP.x - sX/2, centerP.y - sY/2};

    m->tft->drawRect(transP.x, transP.y, sX, sY, color);
}

void DisplayItem::drawRoundRectangleByCenter(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point centerP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    Point transP = {centerP.x - sX/2, centerP.y - sY/2};
    
    m->tft->drawRoundRect(transP.x, transP.y, sX, sY, 4, color);
}

void DisplayItem::drawRoundFilledRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t lx = sizeX*m->getCurrentDisplay()->tileSize*sX/100;
    uint16_t ly = sizeY*m->getCurrentDisplay()->tileSize*sY/100;

    m->tft->fillRoundRect(transP.x, transP.y, lx, ly, 4, color);
}

void DisplayItem::drawFilledRect(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t fillColor){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t lx = sizeX*m->getCurrentDisplay()->tileSize*sX/100;
    uint16_t ly = sizeY*m->getCurrentDisplay()->tileSize*sY/100;

    m->tft->fillRect(transP.x, transP.y, lx, ly, fillColor);
}

/*void DisplayItem::drawFilledRect(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t colorA, uint16_t colorB, bool drawHorizontal){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t lx = sizeX*m->getCurrentDisplay()->tileSize*sX/100;
    uint16_t ly = sizeY*m->getCurrentDisplay()->tileSize*sY/100;

    if(drawHorizontal) m->tft->fillRectHGradient(transP.x, transP.y, lx, ly, colorA, colorB);
    else m->tft->fillRectVGradient(transP.x, transP.y, lx, ly, colorA, colorB);
}*/

void DisplayItem::drawHLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t l = sizeX*m->getCurrentDisplay()->tileSize*length/100;
    m->tft->drawFastHLine(transP.x, transP.y, l, color);
}

void DisplayItem::drawHLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint8_t width, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t l = sizeX*m->getCurrentDisplay()->tileSize*length/100;
    m->tft->drawFastHLine(transP.x, transP.y, l, color);
    for(uint8_t i = 0; i < width; i++){
        m->tft->drawFastHLine(transP.x, transP.y-i, l, color);
        m->tft->drawFastHLine(transP.x, transP.y+i, l, color);
    }
}

void DisplayItem::drawVLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    uint16_t l = sizeY*m->getCurrentDisplay()->tileSize*length/100;
    m->tft->drawFastVLine(transP.x, transP.y, l, color);
}

/*void DisplayItem::drawText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t datum, uint8_t size, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    m->tft->setTextColor(color);
    //m->tft->setTextDatum(datum); //TL_DATUM, TB_DATUM...
    m->tft->setTextSize(size);
    m->tft->text(text.c_str(), transP.x, transP.y);
}*/

void DisplayItem::drawText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t size, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    m->tft->setTextColor(color);
    //canvas->setTextDatum(TL_DATUM); //TL_DATUM, TB_DATUM...
    m->tft->setTextSize(size);
    m->tft->setCursor(transP.x, transP.y);
    m->tft->print(text);
}

void DisplayItem::drawCenteredText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t size, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);

    // Every letter is 6 units in X and 8 in Y.
    transP.x -= text.length()*3*size;
    transP.y -= 4*size;

    m->tft->setTextColor(color);
    //canvas->setTextDatum(TL_DATUM); //TL_DATUM, TB_DATUM...
    m->tft->setTextSize(size);
    m->tft->setCursor(transP.x, transP.y);
    m->tft->print(text);
}

void DisplayItem::drawCircumference(void* menuManager, uint8_t pX, uint8_t pY, uint8_t radius, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    m->tft->drawCircle(transP.x, transP.y, radius, color);
}

void DisplayItem::drawCircle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t radius, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Point transP = transformRelativePoint(m->getCurrentDisplay(), pX, pY);
    m->tft->fillCircle(transP.x, transP.y, radius, color);
}

void DisplayItem::drawGrid(void* menuManager, uint16_t color){
    MenuManager* m = (MenuManager*) menuManager;
    Display* d = m->getCurrentDisplay();
    // Draw tile squares.
    m->tft->drawRect(d->x+d->padLeft, d->y+d->padTop, d->tileSize*d->tileCountX, d->tileSize*d->tileCountY, color);
    //Line 0 has already been drawn.
    for(uint8_t i = 1; i < d->tileCountY; i++)
        m->tft->drawFastHLine(d->x+d->padLeft, d->y+d->padTop+i*d->tileSize, d->tileSize*d->tileCountX, color);
    for(uint8_t i = 1; i < d->tileCountX; i++)
        m->tft->drawFastVLine(d->x+d->padLeft+i*d->tileSize, d->y+d->padTop, d->tileSize*d->tileCountY, color);
}

void DisplayItem::fillTile(void* menuManager, uint8_t x, uint8_t y, uint16_t color){
    const uint8_t lineSeparation = 4;
    MenuManager* m = (MenuManager*) menuManager;
    uint16_t tileSize = m->getCurrentDisplay()->tileSize;

    uint16_t oX = m->getCurrentDisplay()->padLeft + x*tileSize;
    uint16_t oY = m->getCurrentDisplay()->padTop + y*tileSize;

    // This is used so that lines in diferent tiles connect between each other. The trick is that if all lines,
    // starting from (0,0) are separated "lineSeparation" between each other and they're diagonal, then, the sum
    // of both the coordinates, X and Y, always sum a multiple of "lineSeparation". For example, with a separation 
    // of 4, take the line starting from (4,0) -> (3,1) -> (2,2) -> (1,3) -> (0,4). They always sum 4!
    // So when taking a coordinate in the edge of the tile, you just have to round to the upper or bottom multiple of
    // "lineSeparation" (depending if you're drawing from left to right or vice-versa) and start making lines from there
    // on. Now you see it too!
    uint16_t startO = lineSeparation - (oX+oY)%lineSeparation; //Remainder till multiple of lineSeparation
    // Start from upper left corner to the right
    for(uint8_t i = startO; i < m->getCurrentDisplay()->tileSize; i+=lineSeparation){
        m->tft->drawLine(oX + i, oY, oX, oY + i, color);
    }

    uint16_t mX = oX + tileSize-1;
    uint16_t mY = oY + tileSize-1;
    uint16_t startM = (mX+mY)%lineSeparation;
    // Start from bottom right corner to the left
    for(uint8_t i = startM; i < tileSize; i+=lineSeparation){
        m->tft->drawLine(mX - i, mY, mX, mY - i, color);
    }
}