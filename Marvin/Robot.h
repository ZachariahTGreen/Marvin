#ifndef Robot_h
#define Robot_h

#include "Point.h"
#include "World.h"
#include "Arduino.h"

typedef int Angle;

class Robot {
public:
    Robot();
    void turn(Angle);
    void updateCurrentPosition();
    void moveForward(int);
//private:
    Point center;
    Angle facing;
    Servo servoLeft;                             
    Servo servoRight;
};

const int pinFront = 4;
const int pinRight = 2;
const int pinLeft = 8;
const int pinBack = 9;
const int pinFrontRight = 3;
const int pinFrontLeft = 10;

const int pinServoRight = 11;
const int pinServoLeft = 12;

const long forwardSpeed = 5.0;
const int forwardLeftSpeed = 1700;
const int forwardRightSpeed = 1400;

const int leftTurnDuration = 1200;
const int rightTurnAdjustment = 400;
long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return (long)(microseconds / (74 * 2));
}

long getFreeDistance(int pin) {
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  long duration;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  digitalWrite(pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pin, LOW);
  //get reading from Front Sensor
  pinMode(pin, INPUT);
  duration = pulseIn(pin, HIGH);
  delay(100);
  return microsecondsToInches(duration);
}

Robot::Robot() {
  this->center.x = 0;
  this->center.y = 0;
  this->facing = 0.0;
}

void Robot::updateCurrentPosition() {
  long front,left,right,back;
  int xDifference;
  int yDifference;
  for (int i = 0; i < 6; i++) {
    front = getFreeDistance(pinFront) + 4;
    right = getFreeDistance(pinRight) + 3;
    back = getFreeDistance(pinBack) + 4;
    left = getFreeDistance(pinLeft) + 3;
    xDifference = xMax - right - left;
    yDifference = yMax - front - back; 

    if (yDifference == 0){
      this->center.y = back;
    }
    if (xDifference == 0){
      this->center.x = left;
    }
  }
}
void Robot::moveForward(int distance){
  long duration;
  duration = (distance/forwardSpeed) * 1000;
  this->servoLeft.attach(pinServoLeft); 
  this->servoRight.attach(pinServoRight);
  this->servoLeft.writeMicroseconds(forwardLeftSpeed);
  this->servoRight.writeMicroseconds(forwardRightSpeed);
  delay(duration);
  this->servoLeft.detach();
  this->servoRight.detach();
}
void Robot::turn(Angle angle) {
  // Turn Left angle degrees / Turn Right -angle degrees

  boolean isLeft = angle > 0;

  angle = abs(angle);

  // These values come from calibrating the robot and stuff, you know whatevs.
  int directionCode = isLeft ? 1300 : 1700;
  int duration = (int)(angle / 90.0 * leftTurnDuration) - (isLeft ? 0 : rightTurnAdjustment);
  Serial.print(directionCode);
  Serial.print(" ");
  Serial.print(duration);
  Serial.println();

  this->servoLeft.attach(pinServoLeft); 
  this->servoRight.attach(pinServoRight); 
  this->servoLeft.writeMicroseconds(directionCode);
  this->servoRight.writeMicroseconds(directionCode);
  delay(duration);
  this->servoLeft.writeMicroseconds(1500);
  this->servoRight.writeMicroseconds(1500);
  this->servoLeft.detach();
  this->servoRight.detach();
}

#endif

