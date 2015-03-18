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

const int pinServoRight = 11;
const int pinServoLeft = 12;

const long forwardSpeed = 5.0;
const int forwardLeftSpeed = 1700;
const int forwardRightSpeed = 1400;

const int leftTurnDuration = 1200;
const int rightTurnAdjustment = 400;

class Robot {
public:
    Robot();
    void turn(Radians);
    void startPosition();
    void moveForward(int);
    void detectObstacle(World&);
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
