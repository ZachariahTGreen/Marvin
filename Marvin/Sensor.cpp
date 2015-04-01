#include "Sensor.h"

Sensor::Sensor(Robot* robot, Pin pin, Radians orientation, Inches offset) {
    // We assume that the Sensor is pointed directly away from the center of the robot. Is this true? Yes
    this->robot = robot;
    this->pin = pin;
    this->orientation = orientation;
    this->offset = offset;
}

Inches microsecondsToInches(Microseconds microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return (microseconds / (73.746 * 2));
}

Inches Sensor::getFreeDistance() {
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  Pin pin = this->pin;
  Microseconds duration;
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
Inches Sensor::readSample(){
  Inches total = 0;
  Inches high = -1;
  Inches low = -1;
  for(int i = 0; i < SAMPLE_SIZE; i++){
    Inches sample = this->getFreeDistance();
    if (low == -1 || sample < low) { low = sample; }
    if (high == -1 || sample > high) { high = sample; }
    total += sample;
  }
  total -= (low + high);
  return total / (SAMPLE_SIZE - 2);
}
Point Sensor::getObstacle() {
    Inches sampleDistance = this->readSample();
    Radians sensorFacing = this->robot->getOrientation() + this->orientation;
    
    Point center = this->robot->getCenter();

    Point obstacle;
    obstacle.x = center.x + ((this->offset + sampleDistance) * cos(sensorFacing));
    obstacle.y = center.y + ((this->offset + sampleDistance) * sin(sensorFacing));
    
    return obstacle;
}

