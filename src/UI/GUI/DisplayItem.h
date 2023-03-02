#ifndef DISPLAY_ITEM_h
#define DISPLAY_ITEM_h

#include "Arduino.h"
#include <Adafruit_ST7735.h>

struct Point{
    uint16_t x, y;
};

class DisplayItem {
    public:
    uint8_t x, y;           // Tile X, Y
    uint8_t sizeX, sizeY;   // Tile size X, Y

    uint16_t itemID;

    DisplayItem(uint8_t x, uint8_t y, uint8_t sX, uint8_t sY);
    virtual void draw(void* menuManager) = 0;

    bool needsUpdate = true;
    void redraw();

    // General graphic stuff
    Point transformRelativePoint(void* display, uint8_t pX, uint8_t pY);
    uint16_t createColor(uint8_t r, uint8_t g, uint8_t b);

    //General draw functions
    void drawRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color);
    void drawRoundRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color);
    void drawRectangleByCenter(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color);
    void drawRoundRectangleByCenter(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color);

    void drawRoundFilledRectangle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t color);
    void drawFilledRect(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t fillColor);
    //void drawFilledRect(void* menuManager, uint8_t pX, uint8_t pY, uint8_t sX, uint8_t sY, uint16_t colorA, uint16_t colorB, bool drawHorizontal);
    
    void drawHLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint16_t color);
    void drawHLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint8_t width, uint16_t color);
    void drawVLine(void* menuManager, uint8_t pX, uint8_t pY, uint8_t length, uint16_t color);
    
    //void drawText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t datum, uint8_t size, uint16_t color);
    void drawText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t size, uint16_t color);
    void drawCenteredText(void* menuManager, uint8_t pX, uint8_t pY, String text, uint8_t size, uint16_t color);


    void drawCircumference(void* menuManager, uint8_t pX, uint8_t pY, uint8_t radius, uint16_t color);
    void drawCircle(void* menuManager, uint8_t pX, uint8_t pY, uint8_t radius, uint16_t color);

    static void drawGrid(void* menuManager, uint16_t color);
    static void fillTile(void* menuManager, uint8_t x, uint8_t y, uint16_t color);

    public:
    // Number of elements that can be selected inside this item.
    uint8_t selectableCount = 1;

    bool isSelected = false;
    uint8_t selectedElementIndex = 0;
};

#endif