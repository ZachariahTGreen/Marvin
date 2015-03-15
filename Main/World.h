#ifndef World_h
#define World_h

const int xMax = 48;
const int yMax = 78;

class World {
public:
    World();
//private:
    int x[xMax];
    int y[yMax];
};

World::World() {
  for (int i = 0; i < xMax; i++){
    this->x[i] = i+1;
  }
  for (int j = 0; j < yMax; j++){
    this->y[j] = i+1;
  }
}

#endif

