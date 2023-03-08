#include "RotEncoder.h"

const int8_t ROTATION_DIRECTION[16] = {
            0,  -1,   1,  0,
            1,   0,   0, -1,
           -1,   0,   0,  1,
            0,   1,  -1,  0};

RotEncoder::RotEncoder(uint8_t a, uint8_t b){
    this->chA = a;
    this->chB = b;
    pinMode(chA, INPUT);
    pinMode(chA, INPUT_PULLUP);
    pinMode(chB, INPUT);
    pinMode(chB, INPUT_PULLUP);
    lastState = digitalRead(chA) | (digitalRead(chB) << 1);
}

bool RotEncoder::pollState(){
    return rotEncoderState=updateState();
}

/*bool RotEncoder::updateState(){
    bool ret = false;
    uint8_t currentPinState = digitalRead(chA) | (digitalRead(chB) << 1);
    uint32_t currentTime = millis();
    if(currentPinState != lastState){
        if((currentTime - lastTimeChange) > DEFAULT_ROTARY_DEBOUNCE){
            lastTimeChange = currentTime;
            increment = ROTATION_DIRECTION[currentPinState | (lastState << 2)];
            ret =  true;
        }
        lastState = currentPinState;
    }
    return ret;
}*/

bool RotEncoder::updateState(){
  static int8_t rot_enc_table[] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
  static uint8_t prevNextCode = 0;
static uint16_t store=0;

  prevNextCode <<= 2;
  if (digitalRead(chA)) prevNextCode |= 0x02;
  if (digitalRead(chB)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[prevNextCode] ) {
      store <<= 4;
      store |= prevNextCode;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store&0xff)==0x2b){
        increment = -1;
        return true;
      } 
      if ((store&0xff)==0x17){
        increment = 1;
        return true;
      }
   }
   increment = 0;
   return false;
}

int8_t RotEncoder::getIncrement(){
    //if(!updateState()) return 0;
    return rotEncoderState ? increment : 0;
}