#include "GraphWidget.h"

GraphWidget::GraphWidget(uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY) : DisplayItem(x,y,sizeX,sizeY){}

void GraphWidget::draw(void* menuManager){
    // Canvas for the graph with some passing from the border
    drawFilledRect(menuManager, 4,4, 92, 92, 0xFFFF);   // White background

    // Draw the plot line
    const uint8_t totalPlotCount = dataPointsIsFull ? GRAPH_RECORD_SIZE : lastPointIndex;
    if(dataPointsIsFull){
        drawGraphSegment(menuManager, lastPointIndex+1, GRAPH_RECORD_SIZE-1,  0,                                totalPlotCount);
        // Set deltaIndex to the number of points that have already been drawn
        drawGraphSegment(menuManager, 0,                lastPointIndex,   GRAPH_RECORD_SIZE-lastPointIndex-1,   totalPlotCount);
    }else{
        drawGraphSegment(menuManager, 0,                lastPointIndex,     0,                                  totalPlotCount);
    }
}

void GraphWidget::drawGraphSegment(void* menuManager, uint8_t firstIndex, uint8_t lastIndex, uint8_t deltaIndex, const uint8_t totalPlotCount){
    if(firstIndex == lastIndex) return;

    Serial.println("Max " + String(maxValue) + ", Min " + String(minValue));

    uint16_t lastX = 5;
    uint16_t lastY = lerpYCoord(dataPoints[firstIndex]);
    uint8_t counter = deltaIndex+1;
    
    // Firstly draw the passed points
    for(uint8_t i = firstIndex+1; i <= lastIndex; i++){
        uint16_t x = 5 + counter*90/totalPlotCount;
        counter++;
        
        uint16_t y = lerpYCoord(dataPoints[i]);

        Serial.println("("+String(lastX)+"," + String(lastY) + ")  -> ("+String(x)+"," + String(y)+")  Temp: " + String(dataPoints[i]));
        drawLine(menuManager, lastX, lastY, x, y, ST77XX_RED);
        lastX = x;
        lastY = y;
    }
}

uint16_t GraphWidget::lerpYCoord(double data){
    // Lineal interpolation between 5% -> maxVal, x% -> arrayValue, and 90% -> minVal
    return 5 + 85*(data - maxValue)/(minValue - maxValue);
}

void GraphWidget::addPoint(double data){
    lastPointIndex++;
    if(lastPointIndex == GRAPH_RECORD_SIZE){
        dataPointsIsFull = true;
        lastPointIndex = 0;
    }
    dataPoints[lastPointIndex] = data;

    if(data > maxValue) maxValue = data;
    if(data < minValue) minValue = data;
    redraw();
}