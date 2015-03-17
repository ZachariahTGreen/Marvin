#include <Servo.h>
#include "Robot.h"
#include "World.h"

Robot robot;
World world;
Point destination;
void printInformation(){
  Serial.print("(");
  Serial.print(robot.center.x);
  Serial.print(", ");
  Serial.print(robot.center.y);
  Serial.print(")");
  Serial.print(" ");
  Serial.print("(");
  Serial.print(destination.x);
  Serial.print(", ");
  Serial.print(destination.y);
  Serial.print (")");
  Serial.println();
}
void setup() {
  destination.x = 23;
  destination.y = 46;
  Serial.begin(9600);
  robot.updateCurrentPosition();
  printInformation();
}

void loop() {
  robot.updateCurrentPosition();
  printInformation();
  delay(1000);
}

