#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <Alarm.h>
#include <DoorSensor.h>
#include <DoorLock.h>
#include <Locker.h>
#include <LockerWifi.h>
#include <BaseMQTT.h>
#include <LockerMQTTInbound.h>
#include <BaseMQTT.h>
#include <functional>

// BOARD
const int SWITCH_PIN = D3;
const int SERVO_PIN = D5;
const int BUZZER_PIN = D4;
// WIFI
const char* WIFI_SSID = "grego";
const char* WIFI_PASSWORD = "Ed47852169Ra";
// MQTT
const char* MQTT_DOMAIN = "m15.cloudmqtt.com";
const int MQTT_PORT = 14771;
const char* MQTT_CLIENT_ID = "ESP8266Client";
const char* MQTT_USERNAME = "lbwcbjvj";
const char* MQTT_PASSWORD = "eND_kmHSQTYb";

DoorSensor *doorSensor = new DoorSensor(SWITCH_PIN, [](int value) {
  Serial.println(value);
});

DoorLock *doorLock = new DoorLock(SERVO_PIN);
Alarm *alarm = new Alarm(BUZZER_PIN);
Locker *locker = new Locker(alarm, doorSensor, doorLock);

LockerWifi *lockerWifi = new LockerWifi(WIFI_SSID, WIFI_PASSWORD);
WiFiClient espClient;
BaseMQTT *baseMQTT = new BaseMQTT(espClient, MQTT_DOMAIN, MQTT_PORT, mqttCallback);


void setup() {
  Serial.begin(9600);
  Serial.println("System is up");
  lockerWifi->setup();
  baseMQTT->setAuthentication(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
  baseMQTT->setup();
  locker->setup();
}

void loop() {
  locker->loop();
  baseMQTT->loop();
}