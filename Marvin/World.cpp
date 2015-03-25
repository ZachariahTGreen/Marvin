#include "World.h"
#include "math.h"
World::World() {
    for (int i = 0; i < scaledXMax; i++) {
        for (int j = 0; j < scaledYMax; j++) {
            this->grid[i][j] = 0;
        }
    }
}

void World::registerObstacle(Point obstaclePoint) {
  //registers an obstacle into the grid
    this->grid[(int)(obstaclePoint.x / scaleFactor)][(int)(obstaclePoint.y / scaleFactor)] = 1;
}

boolean World::isFree(Point point) {
  //returns if there is an obstacle or not
    return this->grid[(int)(point.x / scaleFactor)][(int)(point.y / scaleFactor)] == 0 && 
        //check for edge of world
        point.x / scaleFactor <= scaledXMax && point.y / scaleFactor <= scaledYMax;
}
boolean World::isGridSectionFree(GridPoint point){
   //Check to make sure all points on the grid section are free
   GridPoint down(point.x, point.y - 1);
   GridPoint left(point.x - 1, point.y);
   GridPoint downLeft(point.x - 1, point.y - 1);
   
   return isFree(point.getPoint()) && isFree(down.getPoint()) 
          && isFree(left.getPoint()) && isFree(downLeft.getPoint());
}
Point World::nextStepNavigate(Point center, Point destination) {
  GridPoint start(center);
  GridPoint target(destination);
  
  // Get adjacent points
  GridPoint up(start.x, start.y + 1);
  GridPoint down(start.x, start.y - 1);
  GridPoint right(start.x + 1, start.y);
  GridPoint left(start.x - 1, start.y);

  const int optionsLength = 4;
  GridPoint options[optionsLength] = {right, up, down, left};

  GridPoint nearest;
  int nearestDistance = 1 << 30; // Just a value too large to ever come out as the minimum, we should hope.

  // Check all options to find the best one.
    for (int i = 0; i < optionsLength; i++){
        GridPoint& option = options[i];
        if (!isGridSectionFree(option)){ continue; }

        int distance = calculateHeuristicDistance(option, target);
        if (distance >= nearestDistance) { continue; }

        nearestDistance = distance;
        nearest = option;
    }

  return nearest.getPoint();
}

int World::calculateHeuristicDistance(GridPoint start, GridPoint target) {
  //calculate Heuristic value (update to work better)
  return abs(target.x - start.x) + abs(target.y - start.y);
}
