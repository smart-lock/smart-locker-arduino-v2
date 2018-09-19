#include "Arduino.h"
#include "Alarm.h"

Alarm::Alarm(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Alarm::printHello() {
  Serial.println("Hello from alarm!");
}
