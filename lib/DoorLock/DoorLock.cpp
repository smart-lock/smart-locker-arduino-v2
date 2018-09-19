#include <DoorLock.h>
#include <Servo.h>

const int SERVO_LOCK_ANGLE = 180;
const int SERVO_UNLOCK_ANGLE = 0;

DoorLock::DoorLock(int servoPin) {
  _servoPin;
}

void DoorLock::loop() {
    
};

void DoorLock::setup() {
  _lockServo.attach(_servoPin);
}

void DoorLock::lock() {
  _locked = true;
  _lockServo.write(SERVO_LOCK_ANGLE);
}

void DoorLock::unlock() {
  _locked = false;
  _lockServo.write(SERVO_UNLOCK_ANGLE);
}