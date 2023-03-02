#include "ButtonInput.h"

ButtonInput::ButtonInput(uint8_t pin){
    this->pin = pin;
}

bool ButtonInput::updateState(){
    bool currentPinState = digitalRead(this->pin);
    uint32_t currentTime = millis();
    //Serial.printf("Curr:%d  Last:%d  Curr:%d Last:%d -> ", currentPinState, lastState, currentTime, lastTimePressed);

    if(currentPinState != lastState){
        bool ret = false;
        if((currentTime - lastTimePressed) > DEFAULT_DEBOUNCE_TIME){
            lastTimePressed = currentTime;
            if(lastState == HIGH && currentPinState == LOW){
                buttonState = RELEASED;
                //Serial.println("RELEASED");
                ret = true;
            }
            if(lastState == LOW && currentPinState == HIGH){
                if((currentTime - doubleClickedTime) < DEFAULT_DOUBLE_CLICK_TIME){
                    repeatedPressesCount++;
                    buttonState = MULTIPLE_CLICK;
                }else{
                    repeatedPressesCount = 1;
                    buttonState = CLICK;
                    startTimePress = currentTime;
                }
                doubleClickedTime = currentTime;
                //Serial.println("CLICK");
                ret = true;
            }
        }
        lastState = currentPinState;
        return ret;
    }

    if(buttonState==CLICK && (currentTime-startTimePress)>DEFAULT_LONG_PRESS_TIME){
        buttonState = LONG_PRESS;
    }
    return false;
}

bool ButtonInput::clicked(){
    // If the state hasn't been updated, then it returns false so that the code that comes
    // after this, doesn't execute.
    // Click is only called once per press.
    return updateState() && buttonState==CLICK;
}

bool ButtonInput::isPressed(){
    updateState();
    return buttonState == CLICK;
}

bool ButtonInput::released(){
    return updateState() && buttonState == RELEASED;
}

bool ButtonInput::clicked(uint8_t timesPressed){
    return updateState() && (buttonState==MULTIPLE_CLICK || (repeatedPressesCount >= timesPressed));
}

bool ButtonInput::doubleClicked(){
    return updateState() && (buttonState==MULTIPLE_CLICK || (repeatedPressesCount > 1));
}