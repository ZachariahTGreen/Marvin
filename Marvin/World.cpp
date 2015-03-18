#include "World.h"
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

