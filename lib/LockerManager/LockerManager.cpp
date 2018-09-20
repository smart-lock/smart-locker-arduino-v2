#include <LockerManager.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Helpers.h>
#include <string.h>
#include <Locker.h>
#include <BaseMQTT.h>

const char CMD_CLAIM = '1';
const char CMD_UNCLAIM = '2';
const char CMD_DEACTIVATE_ALARM = '3';
const char CMD_LOCK ='4';
const char CMD_UNLOCK = '5';
const char CMD_SUDO_DEACTIVATE_ALARM ='6';

// topic:   lockers/<mac-address>/
// payload: <locker-index>:<cmd>:<parameters...>

LockerManager::LockerManager(std::vector<LockerPinGroup> lockerPinGroups, BaseMQTT *baseMQTT) {
  for (LockerPinGroup lockerPinGroup: lockerPinGroups) {
    _lockers.push_back(new Locker(lockerPinGroup.groupId, lockerPinGroup.switchPin, lockerPinGroup.servoPin, lockerPinGroup.buzzerPin));
  }
  _baseMQTT = baseMQTT;
  baseMQTT->setHandler(this);
  // std::transform(lockerPinGroups.begin(), lockerPinGroups.end(), _lockers.begin(), buildLockerFromLockerPinGroup);
}

void LockerManager::init() {

}

void LockerManager::onConnect() {
  String macAddress = WiFi.macAddress();
  String topic = "lockers/" + macAddress;
  Serial.println(topic);
  _baseMQTT->client->subscribe(topic.c_str());
}

Locker* LockerManager::getLockerById (char id) {
  for (Locker* locker: _lockers) {
    if (locker->id == id) {
      return locker;
    }
  }

  return NULL;
}

void LockerManager::onMessage(char* topic, byte* payload, unsigned int length) {
  char lockerIndex = (char)payload[0];
  char cmd = (char)payload[1];

  Locker* targetLocker = this->getLockerById(lockerIndex);
  if (targetLocker == NULL) {
    return;
  }

  Serial.println("Locker found " + String(targetLocker->id));

  switch (cmd) {
    case CMD_CLAIM:
      // claim();
      break;
    case CMD_UNCLAIM:
      Serial.println("[" + String(lockerIndex) + "] received: unclaim");
      // unclaim();
      break;
    case CMD_DEACTIVATE_ALARM:
      Serial.println("[" + String(lockerIndex) + "] received: deactivate_alarm");
      // handleDeactivateAlarmCmd();
      break;
    case CMD_SUDO_DEACTIVATE_ALARM:
      Serial.println("[" + String(lockerIndex) + "] received: sudo_deactivate_alarm");
      // deactivateAlarm();
      break;
    case CMD_LOCK:
      Serial.println("[" + String(lockerIndex) + "] received: lock");
      // handleLockCmd();
      break;
    case CMD_UNLOCK:
      Serial.println("[" + String(lockerIndex) + "] received: unlock");
      // handleUnlockCmd();
      break;
  }
}

void LockerManager::setup() {
  std::for_each(_lockers.begin(), _lockers.end(), [](Locker *locker) { locker->loop(); });
}

void LockerManager::loop() {
  std::for_each(_lockers.begin(), _lockers.end(), [](Locker *locker) { locker->loop(); });
}