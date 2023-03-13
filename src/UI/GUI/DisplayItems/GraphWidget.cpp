#include "GraphWidget.h"

GraphWidget::GraphWidget(uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY) : DisplayItem(x,y,sizeX,sizeY){
    startX = GRAPH_PAD_X;
    startY = 6; // Top padding
    graphWidth = 100 - startX - 2;
    graphHeight = 100 - startY - GRAPH_PAD_Y; 
}

void GraphWidget::draw(void* menuManager){
    drawFilledRect(menuManager, 0,0,100,100,0xafb5ce);
    
    // Canvas for the graph with some passing from the border
    drawFilledRect(menuManager, startX,startY, graphWidth, graphHeight, 0xFFFFFF);   // White background

    // Draw grid
    for(uint8_t i = 0; i <= GRAPH_X_DIVISIONS; i++){
        drawVLine(menuManager, startX + graphWidth*i/GRAPH_X_DIVISIONS, startY, graphHeight, 0x4c6ed3);
    }

    for(uint8_t i = 0; i <= GRAPH_Y_DIVISIONS; i++){
        uint16_t yC = startY+graphHeight*i/GRAPH_Y_DIVISIONS;
        drawHLine(menuManager, startX, yC, graphWidth, 0x4c6ed3);
        
        double lineVal = maxValue + (minValue-maxValue)*i/GRAPH_Y_DIVISIONS;
        int v = lineVal;
        drawText(menuManager, startX, yC, String(v), 1, 0x000000, TEXT_RC);
    }

    if(lastPointIndex == 0xFF) return;  // No points have been added

    // Draw the plot line
    const uint8_t totalLinePlotCount = dataPointsIsFull ? GRAPH_RECORD_SIZE-1 : lastPointIndex;

    uint16_t lastX = startX;
    uint16_t lastY;
    uint8_t deltaIndex = 0;
    if(dataPointsIsFull && lastPointIndex!=GRAPH_RECORD_SIZE-1){
        lastY = lerpYCoord(dataPoints[lastPointIndex+1]);

        drawGraphSegment(menuManager, lastPointIndex+1, GRAPH_RECORD_SIZE-1,    deltaIndex, totalLinePlotCount, lastX, lastY);
        drawGraphSegment(menuManager, 0xFF /*trickery*/,  lastPointIndex,         deltaIndex, totalLinePlotCount, lastX, lastY);
    }else{
        lastY = lerpYCoord(dataPoints[0]);
        drawGraphSegment(menuManager, 0,                lastPointIndex,         deltaIndex, totalLinePlotCount, lastX, lastY);
    }

    // Draw the last measure in the top right corner
    drawText(menuManager, 98, startY+2, String(dataPoints[lastPointIndex]), 1, 0x000000, TEXT_TR);
}

void GraphWidget::drawGraphSegment(void* menuManager, uint8_t firstIndex, uint8_t lastIndex, uint8_t &deltaIndex, const uint8_t totalLinePlotCount, uint16_t &lastX, uint16_t &lastY){
    if(firstIndex == lastIndex) return;

    Serial.println("1st " + String(firstIndex) + ", Last " + String(lastIndex));
    
    // Firstly draw the passed points
    for(uint8_t i = firstIndex+1; i <= lastIndex; i++){
        deltaIndex++;
        uint16_t x = startX + deltaIndex*graphWidth/totalLinePlotCount;
        uint16_t y = lerpYCoord(dataPoints[i]);

        Serial.println("("+String(lastX)+"," + String(lastY) + ")  -> ("+String(x)+"," + String(y)+")  Temp: " + String(dataPoints[i]) + " ind: " + String(deltaIndex));
        drawLine(menuManager, lastX, lastY, x, y, 0xef2828, 2);    // Red line
        lastX = x;
        lastY = y;
    }
}

uint16_t GraphWidget::lerpYCoord(double data){
    // Lineal interpolation between 5% -> maxVal, x% -> arrayValue, and 90% -> minVal
    return startY + (graphHeight-startY)*(data - maxValue)/(minValue - maxValue);
}

void GraphWidget::addPoint(double data){
    lastPointIndex++;
    if(lastPointIndex == GRAPH_RECORD_SIZE){
        dataPointsIsFull = true;
        lastPointIndex = 0;
    }
    dataPoints[lastPointIndex] = data;

    // Maximum and minimum points have to be calculated every time, because the last index can sometimes
    // be removed.
    maxValue = dataPoints[0];
    minValue = dataPoints[0];
    for(uint8_t i = 1; i < (dataPointsIsFull ? GRAPH_RECORD_SIZE : lastPointIndex); i++){
        if(dataPoints[i] > maxValue) maxValue = dataPoints[i];
        else if(dataPoints[i] < minValue) minValue = dataPoints[i];
    }
    // Little trick to give some padding to the top and bottom parts of the graph
    maxValue += 2;
    minValue -= 2;
    if(minValue < 0) minValue = 0;
    redraw();
}