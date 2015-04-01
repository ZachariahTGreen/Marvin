#include <Servo.h>
#include "Robot.h"
#include "World.h"
#include "Sensor.h"
#include "math.h"
#include "Point.h"

Point destination(23, 46);
Robot robot;
World world(destination);

void setup() {
  /*Testing Movement  
  //one spot to the left
  Inches testX = (robot.getCenter().x) - 5;
  Inches testY = (robot.getCenter().y) - 5;
  //test robot's moveTo method
  Point test(testX,testY);
  Serial.begin(9600);
  Serial.print(test.toString());
  robot.moveTo(test);
  */
  
  /*
  robot.startPosition();
  updateWorldObstacles();
  printInformation();
  */
  /*
  robot.startPosition();
  
  while (robot.getCenter().calculateDistance(destination) > 0.5) {
    updateWorldObstacles();
    Point nextNavPoint = world.nextStepNavigate(robot.getCenter(), destination);
    robot.moveTo(nextNavPoint);
  }*/
  /*
  //Test turning
  robot.turn(M_PI_2);
  delay(1000);
  robot.turn(-M_PI_2);
  */
  /*
  //Test Forward Speed
  robot.moveForward(5);
  */   
  
  //reached destination tone
  tone(5, 3000, 1000);
  delay(1000);
}

void loop() { }

void updateWorldObstacles() {
  world.registerObstacle(robot.frontSensor->getObstacle());
  world.registerObstacle(robot.frontRightSensor->getObstacle());
  world.registerObstacle(robot.frontLeftSensor->getObstacle());
  world.registerObstacle(robot.backSensor->getObstacle());
  world.registerObstacle(robot.rightSensor->getObstacle());
  world.registerObstacle(robot.leftSensor->getObstacle());
}
void printInformation(){
    robot.printRobot();
    world.printOGrid();
    world.printHGrid();
}

