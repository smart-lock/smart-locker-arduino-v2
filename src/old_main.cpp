#include <PubSubClient.h>
#include <EEPROM.h>
#include <Servo.h>

#include <Alarm.h>
#include "DebouncedPin.h"
#include <BaseMQTT.h>
#include <LockerOTA.h>
#include <LockerWifi.h>
#include <LockerMQTT.h>
#include <LockerMQTTInbound.h>

// ========== CONSTS =======================
const int SWITCH_PIN = D3;
const int SERVO_PIN = D5;
const int BUZZER_PIN = D4;
const char* WIFI_SSID = "grego";
const char* WIFI_PASSWORD = "Ed47852169Ra";
const char* MQTT_SERVER = "m15.cloudmqtt.com";
uint16_t MQTT_PORT = 14771;
const char* MQTT_CLIENT_ID = "ESP8266Client";
const char* MQTT_USERNAME = "lbwcbjvj";
const char* MQTT_PASSWORD = "eND_kmHSQTYb";

const int SWITCH_READ_INTERVAL = 500;
const int LOCKED_ANGLE = 0;
const int UNLOCKED_ANGLE = 180;
const int LOCKED_ADDR = 0;
// =========================================

// ========= MODULES =======================
// void handlePinChange(int value, bool firstCall) {
//   Serial.println("New value:" + String(value) + " firstCall? "  + String(firstCall));
// }
// DebouncedPin debouncedPin(SWITCH_PIN, 500, handlePinChange);



// ========== VARIABLES =================
unsigned long currentMillis = 0;    // stores the value of millis() in each iteration of loop()

boolean locked = false;
boolean closed = false;
boolean busy = false;
boolean alarm = false;

String deviceId;
// ==================================

LockerWifi wifi(WIFI_SSID, WIFI_PASSWORD);
WiFiClient espClient;
PubSubClient client(espClient);
Servo lockServo;

// ========== SERIAL
void serialSetup() {
  Serial.begin(9600);
}

// ========== WIFI =======================



void printState() {
  Serial.println("===============================");
  Serial.println("locked: " + String(locked));
  Serial.println("closed: " + String(closed));
  Serial.println("busy: " + String(busy));
  Serial.println("alarm: " + String(alarm));
  Serial.println("===============================");
}


void reportState() {
  Serial.println("reporting state as " + deviceId);
  String reportMsg = String(locked) + ":" + String(closed) + ":" + String(busy) + ":" + String(alarm);
  String topic = "locker/" + deviceId + "/report";
  client.publish(topic.c_str(), reportMsg.c_str());
}

//  ========== LOCK ==========
void saveLockState() {
  EEPROM.write(LOCKED_ADDR, locked);
}

void lock() {
  if (!closed) {
    reportError("Tried to lock while open");
    return;
  }
  if (locked) {
    reportError("Tried to lock while locked");
    return;
  }

  locked = true;
  saveLockState();
  reportLocked();
  printState();
}

void unlock() {
  if (!locked) {
    reportError("Tried to unlock while unlocked");
    return;
  }
  locked = false;
  saveLockState();
  reportLocked();
  printState();
}





void recoverLockState() {
  int recoveredLockState = EEPROM.read(LOCKED_ADDR);
  if (recoveredLockState) {
    lock();
  } else {
    unlock();
  }
}

void updateLockerStatus() {
  if (!busy) {
    // the locker is free, it should always be locked!

    if (closed) {
      // if it is on correct position, close it      
      lock();
    }

    if (locked && !closed && !alarm) {
      // if somehow it is locked but not closed, unlock it so it can be properly locked
      unlock();
    }
  }
}

// ========== ALARM ==========
void activateAlarm() {
  tone(BUZZER_PIN, 440);
  alarm = true;
  printState();
  reportAlarm();
  
}

void deactivateAlarm() {
  noTone(BUZZER_PIN);
  alarm = false;
  printState();
  reportAlarm();  

  unlock();
}



// ========== CLAIM ==========
void claim() {
  if (busy) {
    reportError("Tried to claim while busy");
    return;
  }
  busy = true;
  reportBusy();
}

void unclaim() {
  if (!busy) {
    reportError("Tried to claim while free");
    return;
  }
  if (locked) {
    reportError("Tried to unclaim while locked");
    return;
  }
  if (closed) {
    reportError("Tried to unclaim while closed");
    return;
  }
  
  busy = false;
  reportBusy();
  updateLockerStatus();
}


// ========== DOOR ==========
void setClosed(int c) {
  closed = c;
  reportClosed();
  printState();
  
  // If the switch changed state while the locker was closed, it means we have a problem!
  if (locked) {
    activateAlarm();
  }
  
  updateLockerStatus();
}

void doorOpen() {
  setClosed(false);
}

void doorClosed() {
  setClosed(true);
}



// ===== MQTT ============================
BaseMQTT mqtt(espClient, MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD, MQTT_SERVER, MQTT_PORT, callback);

//  ===== SWITCH ============
void switchSetup() {
  pinMode(SWITCH_PIN, INPUT);
}

int previousSwitchState = HIGH;
int lastSwitchHandleMillis = -1;

void switchLoop() {
  int switchState = digitalRead(SWITCH_PIN);
  bool differentRead = switchState != previousSwitchState;
  bool intervalPassedSinceLastRead = currentMillis - lastSwitchHandleMillis > SWITCH_READ_INTERVAL;
  bool firstRead = lastSwitchHandleMillis == -1;
  
  if (firstRead || (differentRead && intervalPassedSinceLastRead)) {
    lastSwitchHandleMillis = currentMillis;
    previousSwitchState = switchState;

    if (switchState == LOW) {
      doorClosed();
    }
    else if (switchState == HIGH) {
      doorOpen();
    }
  }
}

// ======== SERVO ===========
//void servoSetup() {
//  pinMode(SERVO_PIN, OUTPUT);
//  lockServo.attach(SERVO_PIN);
//}

//void servoLoop() {
//  int angle = locked ? LOCKED_ANGLE : UNLOCKED_ANGLE;
//  lockServo.write(angle);
//}

void buzzerSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
}



void setup() {
  serialSetup();
  wifi.setup();
  
  buzzerSetup();
  //  Read last lock state from EPROM  
  recoverLockState();
  //  Report to the server our current state
  reportState();
}

void loop() {
  currentMillis = millis();   // capture the latest value of millis()
  mqtt.loop();
}


