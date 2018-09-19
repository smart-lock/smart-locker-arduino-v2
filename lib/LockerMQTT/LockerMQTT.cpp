#include "Arduino.h"
#include "LockerMQTT.h"

void reportLocked() {
  // Serial.println("reporting locked" + String(locked));
  // client.publish("locker/1/locked", String(locked).c_str());
}

void reportBusy() {
  // Serial.println("reporting busy" + String(busy));
  // client.publish("locker/1/busy", String(busy).c_str());
}

void reportClosed() {
  // Serial.println("reporting closed" + String(closed));
  // client.publish("locker/1/closed", String(closed).c_str());
}

void reportAlarm() {
  // Serial.println("reporting alarm" + String(alarm));
  // client.publish("locker/1/alarm", String(alarm).c_str());
}

void reportError(String error) {
  // Serial.println("reporting error" + String(error));
  // client.publish("locker/1/error", String(error).c_str());  
}