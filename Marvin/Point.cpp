#include "Point.h"
#include "math.h"



Point::Point() {
  this->x = 0;
  this->y = 0;
}

Point::Point(Inches x, Inches y) {
  this->x = x;
  this->y = y;
}

double Point::calculateDistance(Point other){
  return sqrt(square(other.x - this->x) + square(other.y - this->y));
}

void Point::toString() {
  //still working no this
  char buff[6];
  String strx = dtostrf(this->x, 4, 2, buff);
}
