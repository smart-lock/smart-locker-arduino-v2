#include <DoorSensor.h>
#include <DebouncedPin.h>
#include "Arduino.h"

DoorSensor::DoorSensor(int switchPin) {
  _switchPin = switchPin;

  unsigned long delay = 500;
  DebouncedPin _debouncedPin(switchPin, delay);

  _debouncedPin.setHandler(this);
}

void DoorSensor::loop() {
    
};

void DoorSensor::setup() {
  
}

void DoorSensor::onChange(int value, bool firstCall) {
  if (_handler != NULL) {
      if (value == HIGH) {
      _handler->onOpen();
    } else {
      _handler->onClose();
    }
  }
  
}