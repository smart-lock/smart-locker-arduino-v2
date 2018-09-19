#include "Arduino.h"
#include "DebouncedPin.h"

DebouncedPin::DebouncedPin(int pin, unsigned long debounceDelay) {
  _pin = pin;
  _debounceDelay = _debounceDelay;
  _lastPinValue = LOW;
  _lastDebounceTime = 0;
  _firstCall = true;
  _handler = NULL;
}


void DebouncedPin::loop() {
  int newPinValue = digitalRead(_pin);

  if (newPinValue != _lastPinValue) {
    _lastDebounceTime = millis();
  }

  if (millis() > _lastDebounceTime + _debounceDelay) {
    if (newPinValue != _pinValue) {
      _pinValue = newPinValue;
      if (_handler != NULL) {
        _handler->onChange(!newPinValue, _firstCall);
      }
      _firstCall = false;
    }
  }

  _lastPinValue = newPinValue;
}

void DebouncedPin::setup() {
  pinMode(_pin, INPUT);
}

void DebouncedPin::setHandler(DebouncedPinHandler *handler) {
  _handler = handler;
}