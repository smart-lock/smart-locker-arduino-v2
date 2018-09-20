#include <Arduino.h>
#include <Locker.h>
#include <Alarm.h>
#include <DoorLock.h>
#include <DoorSensor.h>
#include <DoorSensor.h>

Locker::Locker(char id, int switchPin, int servoPin, int buzzerPin) {
  this->id = id;
  _doorSensor = new DoorSensor(switchPin);
  _doorLock = new DoorLock(servoPin);
  _alarm = new Alarm(buzzerPin);

  _doorSensor->setSensorHandler(this);
}

bool flag = false;
void Locker::loop() {
  _doorSensor->loop();
}

void Locker::setup() {
  _alarm->setup();
  _doorSensor->setup();
  _doorLock->setup();
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

void Locker::claimLocker() {
  _busy = true;
}

void Locker::freeLocker() {
  _busy = false;
}