#include "Arduino.h"
#include "DebouncedPin.h"

DebouncedPin::DebouncedPin(int pin, unsigned long debounceDelay, void (*onChange)(int value, bool firstCall)) {
  pinMode(pin, INPUT);
  _pin = pin;
  _debounceDelay = _debounceDelay;
  _onChange = onChange;
  _lastPinValue = LOW;
  _lastDebounceTime = 0;
  _firstCall = true;
}

void DebouncedPin::loop() {
  int newPinValue = digitalRead(_pin);

  if (newPinValue != _lastPinValue) {
    _lastDebounceTime = millis();
  }

  if (millis() > _lastDebounceTime + _debounceDelay) {
    if (newPinValue != _pinValue) {
      _pinValue = newPinValue;
      _onChange(!newPinValue, _firstCall);
      _firstCall = false;
    }
  }

  _lastPinValue = newPinValue;
}