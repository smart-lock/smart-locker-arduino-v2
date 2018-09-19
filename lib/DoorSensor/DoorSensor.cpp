#include <DoorSensor.h>
#include <DebouncedPin.h>
#include "Arduino.h"

// void handleSwitchChange (int value, bool firstCall) {
//     if (value == HIGH) {
//       onOpen();
//     } else {
//       onClose();
//     }
//   }

DoorSensor::DoorSensor(int switchPin, void (*onOpen)(void), void (*onClose)(void) ) {
  _switchPin = switchPin;
  unsigned long delay = 500;

  DebouncedPin _debouncedPin(switchPin, delay, [](int value, bool firstCall) {
    
  });
}

void DoorSensor::loop() {
    
};

void DoorSensor::setup() {
  
}