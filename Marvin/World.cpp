#include "World.h"
#include "math.h"
World::World(Point destination) : destination(destination){
    for (int i = 0; i < scaledXMax; i++) {
        for (int j = 0; j < scaledYMax; j++) {
            this->oGrid[i][j] = 0;
        }
    }
    
    this->updateHGrid();
}

void World::resetHGrid(){
  for (int i = 0; i < hGridXMax; i++) {
    for (int j = 0; j < hGridYMax; j++) {
      this->hGrid[i][j] = -1;
    }
  }
}

void World::updateHGrid(){
  this->resetHGrid();
  this->offerHGridValue(this->destination, 0);
}

void World::offerHGridValue(GridPoint cell, int value){
    if(!isGridSectionFree(cell)) { return; }
    if(value > 20) { return; } 

    int gridValue = this->hGrid[cell.x - 1][cell.y - 1];
    if(0 <= gridValue && gridValue <= value) { return; }

    this->hGrid[cell.x - 1][cell.y - 1] = value;
    
    // Print the hGrid at this point in time to see how it all updates.
    //this->printHGrid();
    offerHGridValue(GridPoint(cell.x + 1, cell.y), value + 1);
    offerHGridValue(GridPoint(cell.x - 1, cell.y), value + 1);
    offerHGridValue(GridPoint(cell.x, cell.y + 1), value + 1);
    offerHGridValue(GridPoint(cell.x, cell.y - 1), value + 1);
}

void World::printHGrid(){
  Serial.begin(9600);
  Serial.println("Heuristic Grid:");
    for (int a = 0; a < hGridYMax; a++) {
        for (int b = 0; b < hGridXMax; b++){
            if(this->hGrid[b][a] >=0 && this->hGrid[b][a] < 10) {Serial.print(" ");}
            Serial.print(this->hGrid[b][a]);
            Serial.print("  ");
        }
        Serial.println();
    }
  Serial.println();
  Serial.flush();
  Serial.end();  
}

void World::printOGrid(){
  Serial.begin(9600);
  Serial.println("Obstacle Grid:");
    for (int c = 0; c < scaledYMax; c++) {
        for (int d = 0; d < scaledXMax; d++){
            Serial.print(this->oGrid[d][c]);
            Serial.print("  ");
        }
        Serial.println();
    }
  Serial.println();
  Serial.flush();  
  Serial.end();
}

void World::registerObstacle(Point obstaclePoint) {
    GridPoint gp(obstaclePoint);
    if (oGrid[gp.x][gp.y] == 0) {
        this->oGrid[gp.x][gp.y] = 1;
        updateHGrid();
    }
}

boolean World::isFree(GridPoint point) {
    return (
        0 <= point.x && point.x < scaledXMax &&
        0 <= point.y && point.y < scaledYMax &&
        this->oGrid[point.x][point.y] == 0
    );
}

boolean World::isGridSectionFree(GridPoint point){
   //Check to make sure all points on the grid section are free
   GridPoint down(point.x, point.y - 1); 
   GridPoint left(point.x - 1, point.y);
   GridPoint downLeft(point.x - 1, point.y - 1);
   
   return isFree(point) && isFree(down) && isFree(left) && isFree(downLeft);
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
        GridPoint option = options[i];
        if (!isGridSectionFree(option)) { continue; }

        int distance = calculateHeuristicDistance(option);
        if (distance >= nearestDistance) { continue; }

        nearestDistance = distance;
        nearest = option;
    }

  return nearest.getPoint();
}

int World::calculateHeuristicDistance(GridPoint gp) {
  if (0 > gp.x || gp.x >= hGridXMax || 0 > gp.y || gp.y >= hGridYMax) { return 1 << 10; }
  return this->hGrid[gp.x][gp.y];
}
