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
  return (microseconds / (74 * 2));
}

Inches Sensor::getFreeDistance() {
  Inches total = 0;
  Inches high = -1;
  Inches low = -1;
  for(int i = 0; i < SAMPLE_SIZE; i++){
    Inches sample = this->readSample();
    if (low == -1 || sample < low) { low = sample; }
    if (high == -1 || sample > high) { high = sample; }
    total += sample;
  }
  total -= low;
  total -= high;
  return total / (SAMPLE_SIZE - 2);
}
Inches Sensor::readSample(){
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

Point Sensor::getObstacle() {
        
    Inches sampleDistance = this->getFreeDistance();
        
    Radians sensorFacing = this->robot->getOrientation() + this->orientation;
        
    Point center = this->robot->getCenter();
    Inches sampleDistanceFromCenter = this->offset + sampleDistance; // Here, have loads of printing.
        
    Radians angleFactorX = cos(sensorFacing);
    Radians angleFactorY = sin(sensorFacing);
        
    Inches obsX = center.x + sampleDistanceFromCenter * angleFactorX;
    Inches obsY = center.y + sampleDistanceFromCenter * angleFactorY;
        
    Point obstacle;
    obstacle.x = obsX;//center.x + sampleDistanceFromCenter * cos(sensorFacing); //gets a negative value, when should be like 20s or something
    obstacle.y = obsY;//center.y + sampleDistanceFromCenter * sin(sensorFacing);
            
    return obstacle;    
}

