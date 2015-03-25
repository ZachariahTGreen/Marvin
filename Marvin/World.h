#ifndef World_h
#define World_h

#include <Arduino.h>
#include "Point.h"

const int xMax = 48;
const int yMax = 78;

const int scaleFactor = 4;
const int scaledXMax = xMax / scaleFactor;
const int scaledYMax = yMax / scaleFactor;

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
        this->x = point.x / scaleFactor;
        this->y = point.y / scaleFactor;
    }
    Point getPoint() {
        return Point(this->x * scaleFactor, this->y * scaleFactor);
    }
};

class World {
public:
    World();
    void registerObstacle(Point);
    boolean isFree(Point);
    Point nextStepNavigate(Point, Point);
    boolean isGridSectionFree(GridPoint point);
private:
    short grid[scaledXMax][scaledYMax];
    int calculateHeuristicDistance(GridPoint, GridPoint);
};

#endif

