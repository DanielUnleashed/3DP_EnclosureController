#include "UI/MenuManager.h"

MenuManager::MenuManager(){}

void MenuManager::init(uint8_t CSpin, uint8_t DCpin, uint8_t RESETpin) {
  tft = new TFT(CSpin, DCpin, RESETpin);
  rot = new RotEncoder(ROT_CHA, ROT_CHB);
  but = new ButtonInput(ROT_BUTTON);

  tft->begin();
  tft->setRotation(1);
  tft->fillScreen(0x0000);
}

void MenuManager::update() {
  inputCode = INPUT_NONE;
  if(rot->pollState()) inputCode = INPUT_ROTARY;
  if(but->pollState()){
    if(but->clicked()) inputCode = INPUT_BUTTON_CLICK;
  }
  
  if(petitionToReturnToLastDisplay){
    petitionToReturnToLastDisplay = false;
    
    Serial.println("Return to last screen");
    tft->fillScreen(0x0000);
    currentDisplay--;
    displayCount--;
    Serial.println(displayList[currentDisplay].redrawAll());
  }

  displayList[currentDisplay].renderDisplay(this);

  if(lastWarningTime == 1){
    lastWarningTime = millis();
    tft->fillRect(0,119,160,9, 0x7FF); //Yellow
    tft->setTextColor(0x0000);
    tft->setCursor(1, 120);
    tft->setTextSize(1);
    tft->print(warningMessage);
  }else if(lastWarningTime != 0 && millis()-lastWarningTime >= MENU_MANAGER_WARNING_TIME){
    lastWarningTime = 0;
    tft->fillRect(0,120,160,8, 0x0000);
  }
}

bool MenuManager::addDisplay(Display &display){
  if(displayCount >= MENU_MANAGER_MAX_DISPLAY) return false;
  Serial.println("New display added!");
  currentDisplay = displayCount;
  displayList[displayCount++] = display;
  tft->fillScreen(0x0000);
  return true;
}

Display* MenuManager::getCurrentDisplay(){
  return &displayList[currentDisplay];
}

void MenuManager::returnToLastDisplay(){
  if(currentDisplay == 0) return;
  petitionToReturnToLastDisplay = true;
}

void MenuManager::showWarningMessage(String str){
  lastWarningTime = 1;
  warningMessage = str;
}