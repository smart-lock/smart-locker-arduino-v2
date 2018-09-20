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

  this->printState();
}

bool flag = false;
void Locker::loop() {
  _doorSensor->loop();
}

void Locker::setup() {
  Serial.println("Locker " + String(this->id) + " setup!");
  _alarm->setup();
  _doorSensor->setup();
  _doorLock->setup();
}

void Locker::lockDoor() {
  if (!_doorSensor->closed) {
    return;
  }

  _doorLock->lock();

  this->printState();
}

void Locker::unlockDoor() {
  _doorLock->unlock();

  this->printState();
}

void Locker::onOpen() {
  Serial.println("Locker: onOpen");
  this->printState();
  if (_doorLock->isLocked()) {
    this->soundAlarm();
  }
}

void Locker::onClose() {
  Serial.println("Locker: onClose");
  this->printState();

  if (!this->_busy) {
    this->lockDoor();
  }
}

void Locker::claimLocker() {
  _busy = true;
  this->printState();
}

void Locker::freeLocker() {
  if (_doorLock->isLocked()) {
    // Can not unclaim locker if it is locked;
    return;
  }
  if (_doorSensor->isClosed()) {
    // Can not unclaim locker if it is closed;
    return;
  }
  _busy = false;
  this->printState();
}

void Locker::soundAlarm() {
  this->_alarm->soundAlarm();

  this->printState();
}

void Locker::stopAlarm() {
  if (this->_busy) {
    this->sudoStopAlarm();
  }
}

void Locker::sudoStopAlarm() {
  this->_doorLock->unlock();
  this->printState();
  this->_alarm->stopAlarm();
  this->printState();
}

void Locker::printState() {
  Serial.println("===============================");
  Serial.println("locked: " + String(this->_doorLock->isLocked()));
  Serial.println("closed: " + String(this->_doorSensor->isClosed()));
  Serial.println("busy: " + String(this->_busy));
  Serial.println("alarm: " + String(this->_alarm->isActive()));
  Serial.println("===============================");
}