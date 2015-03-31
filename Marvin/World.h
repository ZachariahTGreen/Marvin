#ifndef World_h
#define World_h

#include <Arduino.h>
#include "Point.h"

const int xMax = 48;
const int yMax = 78;

const int scaleFactor = 4;
const int scaledXMax = (xMax / scaleFactor) + 1;
const int scaledYMax = (yMax / scaleFactor) + 1;
const int hGridXMax = scaledXMax - 1;
const int hGridYMax = scaledYMax - 1;

class GridPoint {
public:
    int x, y;
    GridPoint() {
        this->x = this->y = 0;
    }
    GridPoint(int x, int y) {
        this->x = x;
        this->y = y;
    }
    GridPoint(Point point) {
        this->x = (int)(point.x / scaleFactor);
        this->y = (int)(point.y / scaleFactor);
    }
    Point getPoint() {
        return Point(this->x * scaleFactor, this->y * scaleFactor);
    }
};

class World {
public:
    World(Point);
    void registerObstacle(Point);
    Point nextStepNavigate(Point, Point);
    boolean isGridSectionFree(GridPoint point);
    void printHGrid();
private:
    short oGrid[scaledXMax][scaledYMax];
    int calculateHeuristicDistance(GridPoint);
    
    boolean isFree(GridPoint);

    // Heuristic Grid
    int hGrid[hGridXMax][hGridYMax];
    void resetHGrid();
    void updateHGrid();
    void offerHGridValue(GridPoint cell, int value);
    GridPoint destination;
};

#endif
