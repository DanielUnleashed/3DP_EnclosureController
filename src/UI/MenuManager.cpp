#include "UI/MenuManager.h"

MenuManager::MenuManager(){}

void MenuManager::init(uint8_t CSpin, uint8_t DCpin, uint8_t RESETpin) {
  tft = new Adafruit_ST7735 (CSpin, DCpin, RESETpin);
  rot = new RotEncoder(ROT_CHA, ROT_CHB);

  tft->initR(INITR_BLACKTAB);
  tft->setRotation(1);
  tft->fillScreen(ST7735_BLACK);

  tft->setSPISpeed(8e6);
}

void MenuManager::update() {
  int8_t inc = rot->getIncrement();
  if(inc != 0){
    displayList[currentDisplay].updateSelection(inc>0);
    redrawAll();
  }

  drawTask();
}

void MenuManager::drawTask(){
  displayList[currentDisplay].renderDisplay(this);
}

void MenuManager::redrawAll(){
  displayList[currentDisplay].redrawAll();
}

bool MenuManager::addDisplay(Display display){
  if(displayCount >= MENU_MANAGER_MAX_DISPLAY) return false;
  displayList[displayCount++] = display;
  return true;
}

Display* MenuManager::getCurrentDisplay(){
  return &displayList[currentDisplay];
}