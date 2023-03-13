#ifndef MENU_MANAGER_h
#define MENU_MANAGER_h

#include "Arduino.h"
#include <TFT.h>

#include "UI/GUI/Display.h"

#include "Input/RotEncoder.h"
#include "Input/ButtonInput.h"

#define ROT_CHA A0
#define ROT_CHB A1
#define ROT_BUTTON A2

#define MENU_MANAGER_MAX_DISPLAY 2

#define INPUT_NONE 0
#define INPUT_BUTTON_CLICK 1
#define INPUT_ROTARY 2

#define MENU_MANAGER_WARNING_TIME 10000

class MenuManager{

    public:
    MenuManager();
    void init(uint8_t CSpin, uint8_t DCpin, uint8_t RESETpin);

    // Updates the inputs first, and then decides if it is necessary to update the graphics.
    void update();

    // Inputs (all stored in the MenuManager object)
    TFT* tft;
    RotEncoder* rot;
    ButtonInput* but;

    // Input state
    uint8_t inputCode = INPUT_NONE;

    Display displayList[MENU_MANAGER_MAX_DISPLAY];
    uint8_t displayCount = 0;
    uint8_t currentDisplay = 0;

    bool addDisplay(Display &display);
    Display* getCurrentDisplay();
    void returnToLastDisplay();

    uint32_t lastWarningTime = 0;
    String warningMessage;
    void showWarningMessage(String str);

    private:
    bool petitionToReturnToLastDisplay = false;

};

#endif