#include <Arduino.h>
#include <Locker.h>
#include <Alarm.h>
#include <DoorLock.h>
#include <DoorSensor.h>

Locker::Locker(Alarm *alarm, DoorSensor *doorSensor, DoorLock *doorLock) {
  _alarm = alarm;
  _doorSensor = doorSensor;
  _doorLock = doorLock;

  _doorSensor->setSensorHandler(this);
}

bool flag = false;
void Locker::loop() {
  _doorSensor->loop();

  if (!flag) {
    delay(1000);  
    _alarm->soundAlarm();

    flag = true;
  }
}

void Locker::setup() {
  _alarm->setup();
  _doorSensor->setup();
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