#include <LockerManager.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Helpers.h>
#include <string.h>
#include <Locker.h>
#include <BaseMQTT.h>
#include <BackendService.h>
#include <LockerCluster.h>

const char CMD_CLAIM = '1';
const char CMD_UNCLAIM = '2';
const char CMD_DEACTIVATE_ALARM = '3';
const char CMD_LOCK ='4';
const char CMD_UNLOCK = '5';
const char CMD_SUDO_DEACTIVATE_ALARM ='6';

// topic:   lockers/<mac-address>/
// payload: <locker-index>:<cmd>:<parameters...>

LockerManager::LockerManager(BaseMQTT *baseMQTT, BackendService *backendService) {
  _baseMQTT = baseMQTT;
  _backendService = backendService;
  baseMQTT->setHandler(this);
  _lockerCluster = new LockerCluster();
}

void LockerManager::onStateChange(char id) {
  Locker* locker = this->getLockerByIdInCluster(id);
  if (locker == NULL) {
    return;
  }
  this->publishLockerReport(locker);
}

void LockerManager::publishLockerReport(Locker *locker) {
  String macAddress = WiFi.macAddress();

  String topic = "lockers/" + macAddress + "/" + locker->idInCluster + "/report";
  String payload =
    String(locker->isBusy()) + ":" +
    String(locker->isLocked()) + ":" +
    String(locker->isClosed()) + ":" +
    String(locker->isAlarmActive());

  Serial.println("Reporting");
  Serial.println("Topic: " + topic);
  Serial.println("Payload: " + payload);
  this->_baseMQTT->client->publish(topic.c_str(), payload.c_str());

  
}
void LockerManager::init() {

}

void LockerManager::onConnect() {
  String macAddress = WiFi.macAddress();
  String topic = "lockers/" + macAddress;
  _baseMQTT->client->subscribe(topic.c_str());
}

Locker* LockerManager::getLockerByIdInCluster (char idInCluster) {
  for (Locker* locker: _lockers) {
    if (locker->idInCluster == idInCluster) {
      return locker;
    }
  }

  return NULL;
}

void LockerManager::onMessage(char* topic, byte* payload, unsigned int length) {
  char lockerIndex = (char)payload[0];
  char cmd = (char)payload[1];

  Locker* targetLocker = this->getLockerByIdInCluster(lockerIndex);
  if (targetLocker == NULL) {
    return;
  }

  Serial.println("Locker found " + String(targetLocker->idInCluster));

  switch (cmd) {
    case CMD_CLAIM:
      targetLocker->claimLocker();
      break;
    case CMD_UNCLAIM:
      Serial.println("[" + String(lockerIndex) + "] received: unclaim");
      targetLocker->freeLocker();
      break;
    case CMD_DEACTIVATE_ALARM:
      Serial.println("[" + String(lockerIndex) + "] received: deactivate_alarm");
      targetLocker->stopAlarm();
      break;
    case CMD_SUDO_DEACTIVATE_ALARM:
      Serial.println("[" + String(lockerIndex) + "] received: sudo_deactivate_alarm");
      targetLocker->sudoStopAlarm();
      break;
    case CMD_LOCK:
      Serial.println("[" + String(lockerIndex) + "] received: lock");

      targetLocker->lockDoor();
      break;
    case CMD_UNLOCK:
      Serial.println("[" + String(lockerIndex) + "] received: unlock");

      targetLocker->unlockDoor();
      break;
  }
}


void LockerManager::fetchLockerCluster() {
  String macAddress = WiFi.macAddress();
  auto cluster = std::vector<LockerExternal>();
  _backendService->fetchLockerCluster(macAddress, &cluster);

  for (auto lockerExternal: cluster) {
    Serial.println("New locker  : [" + String(lockerExternal.row) + ", " + String(lockerExternal.column) + "]");
    Locker *locker = new Locker(lockerExternal.idInCluster, lockerExternal.id, lockerExternal.busy, lockerExternal.sensorPin, lockerExternal.lockPin, lockerExternal.alarmPin);
    locker->setLockerStateListener(this);
    _lockers.push_back(locker);
    _lockerCluster->addLocker(lockerExternal.row, lockerExternal.column, locker);
  }
}
void LockerManager::setup() {
  _loading = true;
  this->fetchLockerCluster();
  std::for_each(_lockers.begin(), _lockers.end(), [](Locker *locker) { locker->setup(); });
  _loading = false;
}

void LockerManager::loop() {
  if (_loading) {
    return;
  }
  std::for_each(_lockers.begin(), _lockers.end(), [](Locker *locker) { locker->loop(); });
}
