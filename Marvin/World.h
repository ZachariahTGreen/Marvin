#ifndef World_h
#define World_h

#include <Arduino.h>
#include "Point.h"

const int xMax = 48;
const int yMax = 78;

const int scaleFactor = 3;
const int scaledXMax = xMax / scaleFactor;
const int scaledYMax = yMax / scaleFactor;

class World {
public:
    World();
    void registerObstacle(Point);
    boolean isFree(Point);
//private:
    short grid[scaledXMax][scaledYMax];
};

#endif

