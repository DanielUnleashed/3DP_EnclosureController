#ifndef BUTTONINPUT_h
#define BUTTONINPUT_h

#include "Arduino.h"

#define DEFAULT_DEBOUNCE_TIME 40 //ms
#define DEFAULT_DOUBLE_CLICK_TIME 800 //ms
#define DEFAULT_LONG_PRESS_TIME 1000

class ButtonInput{
    public:
        static const uint8_t RELEASED = 0;
        static const uint8_t CLICK = 1;
        static const uint8_t LONG_PRESS = 2;
        static const uint8_t MULTIPLE_CLICK = 3;

        ButtonInput(uint8_t pin);

        uint8_t pin;

        bool pollState();

        bool clicked();
        bool isPressed();
        bool released(); 
        bool clicked(uint8_t timesPressed);
        bool doubleClicked();

    protected:
        uint32_t startTimePress = 0;
        uint32_t lastTimePressed = 0;
        uint32_t doubleClickedTime = 0;
        bool lastState = LOW;

        uint8_t repeatedPressesCount = 0;
        // Stores the status of the button, it may be one of the values from the upper constants.
        uint8_t buttonState = RELEASED;

        /*Updates the state of the button. Returns true if the state has changed. */
        bool updateState();
        bool buttonPollState = false;
};

#endif