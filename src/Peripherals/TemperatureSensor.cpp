#include "TemperatureSensor.h"
#include "UI/MenuManager.h"

TemperatureSensor::TemperatureSensor(uint8_t dhtPin, uint8_t tmp36) : sensor(DHT(dhtPin, DHTTYPE)){
    this->dhtPin = dhtPin;
    this->tmp36Pin = tmp36;
    pinMode(tmp36Pin, INPUT);
}

void TemperatureSensor::begin(){
    sensor.begin();
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
    Serial.print(getHumidity());
    Serial.print(" CheckDHT= ");
    Serial.println(dhtDown);
}

void TemperatureSensor::update(void* menuManager){
    uint32_t now = millis();
    if(now-lastUpdateTime < TMP_UPDATE_INTERVAL) return;    // Sensor update every TMP_UPDATE_INTERVAL
    currentlySampling = true;

    // Samplings that need a time interval won't stop the microcontroller
    static double average = 0;
    //static double max = 0;
    static uint8_t i = 0, correctDHTSamplings = 0;
    static uint32_t lastSampling = 0;

    static double tempValues[TMP_ITERATIONS], humValues[TMP_ITERATIONS];

    if(i != TMP_ITERATIONS){
        if(now - lastSampling > TMP_ITER_TIME){
            delay(5);
            double tempVoltageOut = analogRead(tmp36Pin)*5.0/1024.0;
            double temp = (tempVoltageOut+1.257)/0.1252;
            average += temp;
            //if(temp > max) max = temp;
            lastSampling = now;

            tempValues[i] = sensor.readTemperature();
            humValues[i] = sensor.readHumidity();
            if(isnan(tempValues[i]) || isnan(humValues[i])) Serial.println("Sampling missed!");
            else correctDHTSamplings++;
            
            i++;
        }
        return; // Wait for the next iteration.
    }

    tmpTemp = average/TMP_ITERATIONS;

    dhtDown = correctDHTSamplings!=TMP_ITERATIONS;
    if(!dhtDown){
        // From the array of samplings, as they are integers, take the most repeated one.
        uint8_t maxRepetitions = 0, maxRepsIndex = 0;
        for(int i = 0; i < TMP_ITERATIONS; i++){
            if(tempValues[i] == -1.0) continue;
            uint8_t repetitions = 1;
            for(int j = i+1; j < TMP_ITERATIONS; j++){
                if(tempValues[j] != -1.0 && tempValues[i] == tempValues[j]){
                    repetitions++;
                    tempValues[j] = -1.0;
                }
            }
            if(repetitions > maxRepetitions){
                maxRepetitions = repetitions;
                maxRepsIndex = i;
            }
        }

        // Check that the increments are being taken degree by degree
        double tempIncrease = dhtTemp-tempValues[maxRepsIndex];
        if(tempIncrease < 0) tempIncrease = -tempIncrease;
        bool increaseIsCorrect = tempIncrease < 3.0 || dhtTemp==0;
        if(maxRepetitions > TMP_ITERATIONS/2 && increaseIsCorrect){
            dhtTemp = tempValues[maxRepsIndex];
            humidity = humValues[maxRepsIndex];
        }else{
            // Repeated samples are wrong!
            dhtDown = true;
        }
    }

    if(dhtDown){
        const String str = "ERROR READING DHT";
        Serial.println(str);
        MenuManager* m = (MenuManager*) menuManager;
        m->showWarningMessage(str);
    }

    currentlySampling = false;
    dataHasBeenRead = false;
    
    lastUpdateTime = now;
    average = 0;
    //max = 0;
    correctDHTSamplings = 0;
    i = 0;
}