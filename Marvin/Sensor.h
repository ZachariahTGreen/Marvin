#ifndef Sensor_h
#define Sensor_h

class Sensor;

#include "Arduino.h"
#include "math.h"
#include "Pin.h"
#include "Point.h"
#include "Robot.h"

typedef double Radians;
typedef float Inches;
typedef long Microseconds;


class Sensor {
public:
    Sensor(Robot*, Pin, Radians, Inches);
    Inches getFreeDistance();
    Point getObstacle();
//private:
    Robot* robot;
    Pin pin;
    Radians orientation;
    Inches offset;
};
#endif
