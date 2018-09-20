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
#include <LockerManager.h>

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


void onConnect(PubSubClient *client) {
  client->subscribe("inTopic");
}

LockerManager *lockerManager = new LockerManager();

Locker *locker = new Locker(SWITCH_PIN, SERVO_PIN, BUZZER_PIN);

LockerWifi *lockerWifi = new LockerWifi(WIFI_SSID, WIFI_PASSWORD);
WiFiClient espClient;
BaseMQTT *baseMQTT = new BaseMQTT(espClient, MQTT_DOMAIN, MQTT_PORT, lockerManager);


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