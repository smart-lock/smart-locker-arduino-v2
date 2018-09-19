#include "Arduino.h"
#include "Alarm.h"

const unsigned long CYCLE_MILLIS = 1000;

Alarm::Alarm(const int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;

  _lastCycle = 0;
}

void Alarm::printHello() {
  Serial.println("Hello from alarm!");
}


void Alarm::setup() {

}

void Alarm::loop() {
  if (millis() > _lastCycle + CYCLE_MILLIS) {
    Serial.println("Hello from alarm cycle");
  }
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