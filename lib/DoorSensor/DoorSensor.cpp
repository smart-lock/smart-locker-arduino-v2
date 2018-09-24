#include <DoorSensor.h>
#include <DebouncedPin.h>
#include "Arduino.h"
#include <functional>

DoorSensor::DoorSensor(uint8_t switchPin) {
  _switchPin = switchPin;

  unsigned long delay = 100;
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
  if (_handler != NULL) {
    // The circuit is closed
    if (value == HIGH) {
      closed = true;
      _handler->onClose();
    } else {
      closed = false;
      _handler->onOpen();
    }
  }
}

bool DoorSensor::isClosed()  {
  return closed;
}