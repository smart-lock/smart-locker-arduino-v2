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
}

void Locker::setup() {
  _alarm->setup();
}