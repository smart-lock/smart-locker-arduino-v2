#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <LockerWifi.h>
#include <BaseMQTT.h>
#include <LockerManager.h>

// BOARD
const int L1_SWITCH_PIN = D3;
const int L1_SERVO_PIN = D5;
const int L1_BUZZER_PIN = D4;

/**
 * T_IRQ
 * T_DO
 * T_DIN
 * T_CS
 * T_CLK
 * VCC - 3.3v
 * GND - GND
 * CS - D0
 * RESET - RST
 * DC - D1
 * SDI/MOSI - D7
 * SCK - D2
 * LED - 3.3v
 * SDO/MISO - D6
 * 
*/

const int LCD_CS = D0;
const int LCD_DC = D1;
const int LCD_SDI = D7;
const int LCD_SCK = D2;
const int LCD_SDO = D6;

// WIFI
const char* WIFI_SSID = "grego";
const char* WIFI_PASSWORD = "Ed47852169Ra";
// MQTT
const char* MQTT_DOMAIN = "m15.cloudmqtt.com";
const int MQTT_PORT = 14771;
const char* MQTT_CLIENT_ID = "ESP8266Client";
const char* MQTT_USERNAME = "lbwcbjvj";
const char* MQTT_PASSWORD = "eND_kmHSQTYb";


std::vector<LockerPinGroup> lockerPinGroups = {{
  '1',
  L1_SWITCH_PIN,
  L1_SERVO_PIN,
  L1_BUZZER_PIN
}};


// Locker *locker = new Locker('1', L1_SWITCH_PIN, L1_SERVO_PIN, L1_BUZZER_PIN);

LockerWifi *lockerWifi = new LockerWifi(WIFI_SSID, WIFI_PASSWORD);
WiFiClient espClient;
BaseMQTT *baseMQTT = new BaseMQTT(espClient, MQTT_DOMAIN, MQTT_PORT);
LockerManager *lockerManager = new LockerManager(lockerPinGroups, baseMQTT);


void setup() {
  Serial.begin(115200);
  Serial.println("System is up");
  lockerWifi->setup();
  baseMQTT->setAuthentication(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD);
  baseMQTT->setup();
  lockerManager->setup();
}

void loop() {
  lockerManager->loop();
  baseMQTT->loop();
}