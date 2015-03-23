#ifndef Robot_h
#define Robot_h

class Robot;
#include "Servo.h"
#include "Arduino.h"
#include "math.h"
#include "Point.h"
#include "World.h"
#include "Sensor.h"
#include "Pin.h"

typedef double Radians;

const Inches verticalOffset = 4;
const Inches horizontalOffset = 3;
const Inches angleOffset = 4;

const long forwardSpeed = 4.0;
const int forwardLeftSpeed = 1700;
const int forwardRightSpeed = 1400;

const int leftTurnDuration = 800;
const int rightTurnAdjustment = 0;

class Robot {
public:
    Robot();
    void turn(Radians);
    void startPosition();
    void moveForward(double);
    Radians getOrientation();
    Point getCenter();
    
//private:
    Point center;
    Radians orientation;
    Servo servoLeft;                             
    Servo servoRight;

    Sensor* frontSensor;
    Sensor* backSensor;
    Sensor* rightSensor;
    Sensor* leftSensor;
    Sensor* frontRightSensor;
    Sensor* frontLeftSensor;
    
    //Sensor& sensors;
};

#endif
