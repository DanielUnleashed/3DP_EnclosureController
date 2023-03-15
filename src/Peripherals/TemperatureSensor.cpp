#include "TemperatureSensor.h"
#include "UI/MenuManager.h"

TemperatureSensor::TemperatureSensor(uint8_t dht, uint8_t tmp36){
    this->dhtPin = dht;
    this->tmp36Pin = tmp36;
    pinMode(tmp36Pin, INPUT);
}

double TemperatureSensor::getTemperature(){
    return dhtDown ? tmpTemp : (tmpTemp+dhtTemp)/2.0;
}

double TemperatureSensor::getHumidity(){
    return humidity;
}

bool TemperatureSensor::dataReady(){
    bool ret = !currentlySampling && !dataHasBeenRead;
    if(!dataHasBeenRead) dataHasBeenRead = true;
    return ret;
}

void TemperatureSensor::printValues(){
    Serial.print("Time= ");
    Serial.print(lastUpdateTime);
    Serial.print(" Temp= ");
    Serial.print(getTemperature());
    Serial.print(" (DHT= " + String(dhtTemp) + ", TMP= " + String(tmpTemp) + ")");
    Serial.print(" Humidity= ");
    Serial.println(getHumidity());
}

void TemperatureSensor::update(void* menuManager){
    uint32_t now = millis();
    if(now-lastUpdateTime < TMP_UPDATE_INTERVAL) return;    // Sensor update every TMP_UPDATE_INTERVAL
    currentlySampling = true;

    // Samplings that need a time interval won't stop the microcontroller
    static double average = 0;
    static double max = 0;
    static uint8_t i = 0;
    static uint32_t lastSampling = 0;

    if(i != TMP_ITERATIONS){
        if(now - lastSampling > TMP_ITER_TIME){
            delay(5);
            double tempVoltageOut = analogRead(tmp36Pin)*5.0/1024.0;
            double temp = (tempVoltageOut+1.257)/0.1252;
            average += temp;
            if(temp > max) max = temp;
            lastSampling = now;
            i++;
        }
        return; // Wait for the next iteration.
    }

    double temp = average/TMP_ITERATIONS;
    tmpTemp = (max+temp)/2.0;

    int chk = DHT.read11(dhtPin);
    dhtDown = chk!=DHTLIB_OK;
    if(chk == DHTLIB_OK){
        dhtTemp = DHT.temperature;
        humidity = DHT.humidity;
    }else{
        const String str = "ERROR READING DHT";
        Serial.println(str);
        MenuManager* m = (MenuManager*) menuManager;
        m->showWarningMessage(str);
    }

    currentlySampling = false;
    dataHasBeenRead = false;
    
    lastUpdateTime = now;
    average = 0;
    max = 0;
    i = 0;
}