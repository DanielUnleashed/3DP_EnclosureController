#ifndef DISPLAY_h
#define DISPLAY_h

#include "Arduino.h"
#include "DisplayItem.h"

#define DISPLAY_MAX_ELEMENTS 5

class Display{
    public:
    Display(uint8_t x = 0, uint8_t y = 0, uint16_t width = 160, uint16_t height = 128, uint8_t tileCountX = 6, uint8_t tileCountY = 4);

    DisplayItem* items[DISPLAY_MAX_ELEMENTS];
    uint8_t itemCount = 0;

    bool addItem(DisplayItem*);
    bool removeItem(DisplayItem*);
    int8_t findItem(DisplayItem*);

    void renderDisplay(void* menuManager);

    // When true, rotating the encoder will select diferent elements inside the display.
    bool traversingWidgetMode = true;

    uint16_t x, y;
    uint16_t width, height;
    uint8_t tileCountX, tileCountY;

    // When centerAlign is true, everything will be centered on the screen, and the values from 
    // the padding will be automatically calculated.
    bool centerAlign = true;
    uint8_t padTop = 0, padBot = 0, padLeft = 0, padRight = 0;

    uint16_t tileSize;

    void redrawAll();

    private:
    void calculateTileSize();
    
    public:
    // Selection stuff
    uint8_t selectedItem = 0;   // The item being selected
    void updateSelection(bool increment);

};

#endif