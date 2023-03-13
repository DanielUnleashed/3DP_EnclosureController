#ifndef GRAPH_WIDGET_h
#define GRAPH_WIDGET_h

#include "UI/GUI/DisplayItem.h"

#define GRAPH_RECORD_SIZE 8
#define GRAPH_X_DIVISIONS 5
#define GRAPH_Y_DIVISIONS 4

#define GRAPH_PAD_X 10
#define GRAPH_PAD_Y 15

class GraphWidget : public DisplayItem {
    public:
    GraphWidget(uint8_t x, uint8_t y, uint8_t sizeX, uint8_t sizeY);

    double dataPoints[GRAPH_RECORD_SIZE];
    // The data will be added from the beginning again, overwriting existing data.
    // This is so that the array won't have to be constantly reordered each time a 
    // new data point is added.
    bool dataPointsIsFull = false;
    uint8_t lastPointIndex = 0xFF;

    double maxValue, minValue;

    void addPoint(double data);

    void draw(void* menuManager) override;

    private:
    void drawGraphSegment(void* menuManager, uint8_t firstIndex, uint8_t lastIndex, uint8_t &deltaIndex, const uint8_t totalPlotCount, uint16_t &lastX, uint16_t &lastY);
    uint16_t lerpYCoord(double val);

    uint16_t startX, startY, graphWidth, graphHeight;

};

#endif