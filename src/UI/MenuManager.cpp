#include "UI/MenuManager.h"

MenuManager::MenuManager(){}

void MenuManager::init(uint8_t CSpin, uint8_t DCpin, uint8_t RESETpin) {
  tft = new Adafruit_ST7735 (CSpin, DCpin, RESETpin);
  rot = new RotEncoder(ROT_CHA, ROT_CHB);
  but = new ButtonInput(ROT_BUTTON);

  tft->initR(INITR_BLACKTAB);
  tft->setRotation(1);
  tft->fillScreen(ST7735_BLACK);

  tft->setSPISpeed(8e6);
}

void MenuManager::update() {
  inputCode = INPUT_NONE;
  if(but->pollState()) inputCode = INPUT_BUTTON_CLICK;
  if(rot->pollState()) inputCode = INPUT_ROTARY;
  
  displayList[currentDisplay].renderDisplay(this);
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