#ifndef DISPLAY_ITEM_h
#define DISPLAY_ITEM_h

#include "Arduino.h"
#include <TFT.h>

struct Point{
    uint16_t x, y;
};

#define TEXT_TL 0   // Text top, left
#define TEXT_CC 1   // Text x-centered and y-centered
#define TEXT_RC 2   // Text right and y-centered 
#define TEXT_LC 3   // Text left centered

class DisplayItem {
    public:
    uint8_t x, y;           // Tile X, Y
    uint8_t sizeX, sizeY;   // Tile size X, Y

    uint16_t itemID;

    DisplayItem(uint8_t x, uint8_t y, uint8_t sX, uint8_t sY);
    virtual void draw(void* menuManager) = 0;
    virtual void handleInput(void* menuManager);

    bool needsUpdate = true;
    void redraw();

    // General graphic stuff
    Point transformRelativePoint(void* display, uint8_t pX, uint8_t pY);
    uint16_t createColor(uint8_t r, uint8_t g, uint8_t b);

    //General draw functions
    void calculateRectangleData(void* m, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint32_t &color, Point &transP, uint16_t &lx, uint16_t &ly);
    void drawRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint32_t color);
    void drawRoundRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint32_t color);

    void drawRoundFilledRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint32_t color);
    void drawFilledRect(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint32_t color);
    //void drawFilledRect(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint32_t colorA, uint32_t colorB, bool drawHorizontal);
    
    void drawLine(void* menuManager, uint8_t oX, uint8_t oY, uint8_t pX, uint8_t pY, uint32_t color);
    void drawHLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint32_t color);
    void drawHLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint8_t width, uint32_t color);
    void drawVLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint32_t color);
    
    //void drawText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t datum, uint8_t size, uint32_t color);
    void drawText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t size, uint32_t color, uint8_t datum = TEXT_TL);

    void drawCircumference(void* menuManager, uint8_t pX, uint8_t pY, uint8_t radius, uint32_t color);
    void drawCircle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t radius, uint32_t color);

    static void drawGrid(void* menuManager, uint32_t color);
    static void fillTile(void* menuManager, uint8_t x, uint8_t y, uint32_t color);

    public:
    // Number of elements that can be selected inside this item.
    uint8_t selectableCount = 1;

    bool isSelected = false;
    uint8_t selectedElementIndex = 0;

    bool drawItemSelectedSquare = true;
};

#endif