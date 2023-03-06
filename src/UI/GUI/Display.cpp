#include "Display.h"
#include "UI/MenuManager.h"

Display::Display(uint8_t x, uint8_t y, uint16_t width, uint16_t height, uint8_t tileCountX, uint8_t tileCountY){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->tileCountX = tileCountX;
    this->tileCountY = tileCountY;
    calculateTileSize();
}

bool Display::addItem(DisplayItem* item){
    if(itemCount >= DISPLAY_MAX_ELEMENTS) return false;
    items[itemCount++] = item;
    return true;
}

bool Display::removeItem(DisplayItem* item){
    int8_t index = findItem(item);
    if(index != -1){
        items[index] = items[--itemCount];
    }
    return index != -1;
}

int8_t Display::findItem(DisplayItem* item){
    for(uint8_t i = 0; i < itemCount; i++){
        if(items[i]->itemID == item->itemID) return i;
    }
    return -1;
}

void Display::renderDisplay(void* menuManager){
    MenuManager* m = (MenuManager*) menuManager;
    if(traversingWidgetMode && m->inputCode == INPUT_ROTARY){
        updateSelection(m->rot->getIncrement() > 0);
        redrawAll();
        m->inputCode = INPUT_NONE; // Disable so the selected item doesn't do anything funky.
    }else if(m->inputCode != INPUT_NONE){
        items[selectedItem]->handleInput(menuManager);
    }

    items[selectedItem]->isSelected = true;
    for(uint8_t i = 0; i < itemCount; i++){
        if(items[i]->needsUpdate){
            items[i]->needsUpdate = false;
            items[i]->draw(menuManager);

            if(selectedItem==i){
                items[i]->drawRectangle(menuManager, 0,0,100,100, 0xfec5); // Cool yellow (?)
            }            
        }

    }
}

void Display::redrawAll(){
    for(DisplayItem* d : items){
        d->redraw();
    }
}

void Display::calculateTileSize(){
    uint16_t realW = width - padLeft - padRight;
    uint16_t realH = height - padTop - padBot;

    uint16_t desiredTileSizeX = realW/tileCountX;
    uint16_t desiredTileSizeY = realH/tileCountY;

    if(desiredTileSizeX < desiredTileSizeY){
        tileSize = desiredTileSizeX;
    }else{
        tileSize = desiredTileSizeY;
    }
    //Serial.println("TileSize: " + String(tileSize));

    // Recalculate padding to fix rounding errors
    uint16_t xError = width - tileCountX*tileSize;
    uint16_t yError = height - tileCountY*tileSize;

    if(centerAlign){
        padLeft = xError/2;
        padRight = xError - padLeft;
        padTop = yError/2;
        padBot = yError - padTop;
    }else{
        // Give proportional padding using the current padding values
        // To fix rounding errors, top and left have prioritized accuracy, right and bot
        // are being rounded up.
        if(padLeft+padRight != 0){
            padLeft = xError*padLeft/(padLeft+padRight);
        }
        padRight = xError - padLeft;

        if(padTop+padBot != 0){
            padTop = yError*padTop/(padTop+padBot);
        }
        padBot = yError - padTop;
    }
}

void Display::updateSelection(bool increment){
    uint8_t innerSelection = items[selectedItem]->selectedElementIndex;
    if(increment){
        if(innerSelection == items[selectedItem]->selectableCount-1){
            if(++selectedItem == itemCount) selectedItem = 0;
            items[selectedItem]->selectedElementIndex = 0;
        }else{
            items[selectedItem]->selectedElementIndex++;
        }
    }else{
        if(innerSelection == 0){
            if(selectedItem == 0) selectedItem = itemCount-1;
            else selectedItem--; 
            items[selectedItem]->selectedElementIndex = items[selectedItem]->selectableCount-1;
        }else{
            items[selectedItem]->selectedElementIndex--;
        }
    }

}