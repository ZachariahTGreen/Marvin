#ifndef World_h
#define World_h

const int xMax = 48;
const int yMax = 78;

struct World {   
    int x[xMax];
    int y[yMax];
};
typedef struct World World;

void initializeWorld(World* world) {
  int X = 1;
  int Y = 1;
  for (int k; k < xMax; k++){
    world->x[k] = X;
    X++;  
  }
  for (int j; j < yMax; j++){
    world->y[j] = Y;
    Y++; 
  }
}

#endif

