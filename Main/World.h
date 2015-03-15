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

World::World() {
    for (int i = 0; i < scaledXMax; i++) {
        for (int j = 0; j < scaledYMax; j++) {
            this->grid[i][j] = 0;
        }
    }
}

void World::registerObstacle(Point obstaclePoint) {
    this->grid[(int)(obstaclePoint.x / scaleFactor)][(int)(obstaclePoint.y / scaleFactor)] = 1;
}

boolean World::isFree(Point point) {
    return this->grid[(int)(point.x / scaleFactor)][(int)(point.y / scaleFactor)] == 0;
}

#endif

