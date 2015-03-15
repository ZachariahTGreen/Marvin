#include <Servo.h>
#include "Robot.h"
#include "World.h"

Robot robot;
World world;
void setup() {
  Serial.begin(9600);
  robot.turn(90);
}

void loop() {
  robot.updateCurrentPosition();
  Serial.print("(");
  Serial.print(robot.center.x);
  Serial.print(", ");
  Serial.print(robot.center.y);
  Serial.print (")");
  Serial.println();
  delay(1000);
}
