#include <Servo.h>
#include "Robot.h"
#include "World.h"
#include "Sensor.h"
#include "math.h"
#include "Point.h"

Robot robot;
World world;
Point destination;
void printPoint(Point point){
  Serial.print("(");
  Serial.print(point.x);
  Serial.print(", ");
  Serial.print(point.y);
  Serial.print(")");
  Serial.print(" ");
}
void printInformation(){
  printPoint(robot.getCenter());
  printPoint(destination);
  Serial.println();
}
void setup() {
  
  /*  //Test turning
  robot.turn(M_PI_2);
  delay(1000);
  robot.turn(-M_PI_2);
  */
  destination.x = 23;
  destination.y = 46;
  Serial.begin(9600);
  double distance;
  robot.startPosition();
  printInformation();
  //Test without obstacles
  
  adjustHeadingTowardsDestination(destination, robot);
  distance = calculateDistance(robot.getCenter(), destination);
  robot.moveForward(distance);
  printInformation();
  /*
  //detect obstacles and update world grid
  world.registerObstacle(robot.frontSensor->getObstacle());
  world.registerObstacle(robot.frontRightSensor->getObstacle());
  world.registerObstacle(robot.frontLeftSensor->getObstacle());
  */
  
  //reached destination tone
  tone(5, 3000, 1000);                     
  delay(1000);                               

}

void loop() {

}
void adjustHeadingTowardsDestination(Point heading, Robot robot){
  // adjusts heading toward destination
  double Yheading, Xheading, headingRadians;
  Point center = robot.getCenter();
  Xheading = destination.x - center.x;
  Yheading = destination.y - center.y;
  Serial.print(Xheading);
  Serial.print(" ");
  Serial.print(Yheading);
  Serial.print(" ");
  headingRadians = atan2(Xheading, Yheading);
  Serial.print(headingRadians);
  robot.turn(abs(headingRadians));
}
double calculateDistance(Point center, Point destination){
  double distance;
  distance = sqrt(square(destination.x - center.x) + square(destination.y - center.y));
  return distance;
}


