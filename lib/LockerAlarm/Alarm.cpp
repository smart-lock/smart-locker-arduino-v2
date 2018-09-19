#include "Arduino.h"
#include "Alarm.h"

const unsigned long CYCLE_MILLIS = 1000;

Alarm::Alarm(const int pin)
{
  _pin = pin;
  _lastCycle = 0;
}

void Alarm::printHello() {
  Serial.println("Hello from alarm!");
}


void Alarm::setup() {
  pinMode(_pin, OUTPUT);
}

void Alarm::loop() {

}

bool Alarm::isActive() {
  return _active;
}

void Alarm::soundAlarm() {
  tone(_pin, 440);
  _active = true;
}

void Alarm::stopAlarm() {
  noTone(_pin);
  _active = false;
}