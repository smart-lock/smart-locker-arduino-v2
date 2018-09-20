#include <DoorSensor.h>
#include <DebouncedPin.h>
#include "Arduino.h"
#include <functional>

DoorSensor::DoorSensor(int switchPin) {
  _switchPin = switchPin;

  unsigned long delay = 500;
  _debouncedPin = new DebouncedPin(switchPin, delay);

  _debouncedPin->setHandler(this);
}

void DoorSensor::loop() {
  _debouncedPin->loop();
};

void DoorSensor::setup() {
  _debouncedPin->setup();
}


void DoorSensor::setSensorHandler(DoorSensorHandler *handler) {
  _handler = handler;
}
void DoorSensor::onChange(int value, bool firstCall) {
  Serial.println("here: " + value);
  if (_handler != NULL) {
      // The circuit is closed
      if (value == HIGH) {
      _handler->onClose();
    } else {
      _handler->onOpen();
    }
  }
  
}