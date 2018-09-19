#include <Arduino.h>
#include <Alarm.h>
#include <DoorSensor.h>
#include <DoorLock.h>
#include <Locker.h>
#include <functional>

const int SWITCH_PIN = D3;
const int SERVO_PIN = D5;
const int BUZZER_PIN = D4;

DoorSensor *doorSensor = new DoorSensor(SWITCH_PIN, [](int value) {
  Serial.println(value);
});

DoorLock *doorLock = new DoorLock(SERVO_PIN);
Alarm *alarm = new Alarm(BUZZER_PIN);
Locker *locker = new Locker(alarm, doorSensor, doorLock);

void setup() {
  Serial.begin(9600);
  Serial.println("System is up");
  locker->setup();
}

void loop() {
  locker->loop();
}