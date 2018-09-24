#include <Arduino.h>
#include <Locker.h>
#include <Alarm.h>
#include <DoorLock.h>
#include <DoorSensor.h>
#include <DoorSensor.h>

Locker::Locker(char idInCluster, const char* id, bool busy, uint8_t switchPin, uint8_t servoPin, uint8_t buzzerPin) {
  this->idInCluster = idInCluster;
  this->id = id;
  this->_doorSensor = new DoorSensor(switchPin);
  this->_doorLock = new DoorLock(servoPin);
  this->_alarm = new Alarm(buzzerPin);
  this->_busy = busy;
  this->_doorSensor->setSensorHandler(this);
  this->_lockerStateListener = NULL;
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
  if (!_doorSensor->isClosed() || _doorLock->isLocked()) {
    return;
  }

  _doorLock->lock();

  this->printState();
  this->reportToStateListener();
}

void Locker::unlockDoor() {
  _doorLock->unlock();

  this->printState();
  this->reportToStateListener();
}

void Locker::onOpen() {
  Serial.println("Locker: onOpen");
  this->printState();
  this->reportToStateListener();
  if (_doorLock->isLocked()) {
    this->soundAlarm();
  }
}

void Locker::onClose() {
  Serial.println("Locker: onClose");
  this->printState();
  this->reportToStateListener();

  if (!this->_busy) {
    this->lockDoor();
  }
}

void Locker::claimLocker() {
  _busy = true;
  this->printState();
  this->reportToStateListener();
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
  this->reportToStateListener();
}

void Locker::soundAlarm() {
  if (!this->_alarm->isActive()) {
    return;
  }
  this->_alarm->soundAlarm();

  this->printState();
  this->reportToStateListener();
}

void Locker::stopAlarm() {
  if (this->_busy) {
    this->sudoStopAlarm();
  }
}

void Locker::sudoStopAlarm() {
  this->_doorLock->unlock();
  this->printState();
  this->reportToStateListener();
  this->_alarm->stopAlarm();
  this->printState();
  this->reportToStateListener();
}

void Locker::printState() {
  Serial.println("===============================");
  Serial.println("locked: " + String(this->_doorLock->isLocked()));
  Serial.println("closed: " + String(this->_doorSensor->isClosed()));
  Serial.println("busy: " + String(this->_busy));
  Serial.println("alarm: " + String(this->_alarm->isActive()));
  Serial.println("===============================");
}

void Locker::reportToStateListener() {
  if (this->_lockerStateListener != NULL) {
    this->_lockerStateListener->onStateChange(this->idInCluster);
  }
}
void Locker::setLockerStateListener(LockerStateListener *lockerStateListener) {
  _lockerStateListener = lockerStateListener;
}

bool Locker::isBusy() {
  return _busy;
}
bool Locker::isClosed() {
  return _doorSensor->isClosed();
}
bool Locker::isLocked() {
  return _doorLock->isLocked();
}
bool Locker::isAlarmActive() {
  return _alarm->isActive();
}