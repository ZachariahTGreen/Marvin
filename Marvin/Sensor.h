#ifndef Sensor_h
#define Sensor_h

class Sensor;

#include "Arduino.h"
#include "math.h"
#include "InputOutput.h"
#include "Point.h"
#include "Robot.h"

const int SAMPLE_SIZE = 6;

class Sensor {
public:
    Sensor(Robot*, InputOutput, Radians, Inches);
    Inches getFreeDistance();
    Point getObstacle();
//private:
    Robot* robot;
    InputOutput pin;
    Radians orientation;
    Inches offset;
    Inches readSample();
};
#endif
