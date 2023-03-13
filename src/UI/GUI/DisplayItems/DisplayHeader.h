#ifndef DISPLAY_HEADER_h
#define DISPLAY_HEADER_h

#include "UI/GUI/DisplayItem.h"

class DisplayHeader : public DisplayItem {
    public:
    DisplayHeader(String headerName, uint8_t sizeX, uint8_t sizeY = 1);

    String headerName;

    void draw(void* menuManager) override;
    void handleInput(void* menuManager);

};

#endif