#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <LockerWifi.h>
#include <BaseMQTT.h>
#include <LockerManager.h>
#include <View.h>
#include <LockerCluster.h>
#include <Locker.h>
#include <BackendService.h>

// BOARD
const int L1_SWITCH_PIN = D4; // 5
const int L1_SERVO_PIN = D0;  // 16
const int L1_BUZZER_PIN = D8; // 4

// WIFI
const char* WIFI_SSID = "grego";
const char* WIFI_PASSWORD = "Ed47852169Ra";
// MQTT
const char* MQTT_DOMAIN = "m15.cloudmqtt.com";
const int MQTT_PORT = 14771;
const char* MQTT_CLIENT_ID = "ESP8266Client";
const char* MQTT_USERNAME = "lbwcbjvj";
const char* MQTT_PASSWORD = "eND_kmHSQTYb";
// HTTP
const char* HTTP_DOMAIN = "192.168.1.34";
const int HTTP_PORT = 3003;

LockerWifi *lockerWifi = new LockerWifi(WIFI_SSID, WIFI_PASSWORD);
WiFiClient espClient;
BaseMQTT *baseMQTT = new BaseMQTT(espClient, MQTT_DOMAIN, MQTT_PORT);
BackendService *backendService = new BackendService(espClient, HTTP_DOMAIN, HTTP_PORT);
View *view = new View();
LockerManager *lockerManager = new LockerManager(baseMQTT, backendService, view);

void setup() {
  Serial.begin(115200);
  lockerWifi->setup();
  baseMQTT->setAuthentication(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
  baseMQTT->setup();
  view->setup();
  lockerManager->setup();
}

void loop() {
  lockerManager->loop();
  baseMQTT->loop();
  view->loop();

}