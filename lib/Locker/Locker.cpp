#include <Arduino.h>
#include <Locker.h>
#include <Alarm.h>
#include <DoorLock.h>
#include <DoorSensor.h>

Locker::Locker(Alarm *alarm, DoorSensor *doorSensor, DoorLock *doorLock) {
  _alarm = alarm;
  _doorSensor = doorSensor;
  _doorLock = doorLock;
}

void Locker::loop() {
  _alarm->loop();
  _doorSensor->loop();
}

void Locker::setup() {
  _alarm->setup();
  _doorSensor->loop();
}

void Locker::lockDoor() {
  if (!_doorSensor->closed) {
    return;
  }

  _doorLock->lock();
}

void Locker::unlockDoor() {
  _doorLock->unlock();
}

void Locker::onOpen() {
  Serial.println("Locker: onOpen");
}

void Locker::onClose() {
  Serial.println("Locker: onClose");
}