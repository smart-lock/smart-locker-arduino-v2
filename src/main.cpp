#include <Arduino.h>
#include <Alarm.h>
#include <DoorSensor.h>
#include <DoorLock.h>
#include <Locker.h>

const int ALARM_PIN = D3;
const int SWITCH_PIN = D4;
const int BUZZER_PIN = D5;

DoorSensor *doorSensor = new DoorSensor(SWITCH_PIN);
DoorLock *doorLock = new DoorLock(BUZZER_PIN);
Alarm *alarm = new Alarm(ALARM_PIN);
Locker locker(alarm, doorSensor, doorLock);

void setup() {
  
}

void loop() {

}