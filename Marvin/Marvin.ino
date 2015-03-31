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
  robot.startPosition();
  robot.printRobot();
  world.printOGrid();
  world.printHGrid();
  
  
  //
  
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


